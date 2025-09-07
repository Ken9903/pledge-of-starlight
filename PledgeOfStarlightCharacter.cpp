// Copyright Epic Games, Inc. All Rights Reserved.

#include "PledgeOfStarlightCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APledgeOfStarlightCharacter

APledgeOfStarlightCharacter::APledgeOfStarlightCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	PlayerAbility = CreateDefaultSubobject<UPOSPlayerAbility>(TEXT("PlayerAbility"));
	PlayerInventory = CreateDefaultSubobject<UPOSPlayerInventory>(TEXT("PlayerInventory"));
	ComboComponent = CreateDefaultSubobject<UPOSComboComponent>(TEXT("ComboComponent"));

	SkillGimmickTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SkillGimmickTrigger"));
	SkillGimmickTrigger->SetupAttachment(RootComponent);
	SkillGimmickTrigger->SetSphereRadius(150.0f);
	//SkillGimmickTrigger->SetCollisionProfileName(TEXT("")); // 추가 고려
}

UPOSPlayerAbility* APledgeOfStarlightCharacter::GetPlayerAbility()
{
	return PlayerAbility;
}

UPOSPlayerInventory* APledgeOfStarlightCharacter::GetPlayerInventory()
{
	return PlayerInventory;
}

UPOSNPCDialogueHighlightWidget* APledgeOfStarlightCharacter::GetNPCDialogueHighlightWidget()
{
	return NPCDialogueHighlightWidget;
}

void APledgeOfStarlightCharacter::SetNPCDialogueHighlightWidget(UPOSNPCDialogueHighlightWidget* InNPCDialogueHighlightWidget)
{
	NPCDialogueHighlightWidget = InNPCDialogueHighlightWidget;
	return;
}

void APledgeOfStarlightCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	SkillGimmickTrigger->OnComponentBeginOverlap.AddDynamic(this, &APledgeOfStarlightCharacter::OnSkillGimmickCollisionBeginOverlap);
	SkillGimmickTrigger->OnComponentEndOverlap.AddDynamic(this, &APledgeOfStarlightCharacter::OnSkillGimmickCollisionEndOverlap);
}

void APledgeOfStarlightCharacter::OnSkillGimmickCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	IPOSGimmickInteractInterface* GimmickInteractInterface = Cast<IPOSGimmickInteractInterface>(OtherActor);
	if(GimmickInteractInterface)
	{
		GimmickInteractObjectList.Emplace(GimmickInteractInterface);
	}
}

void APledgeOfStarlightCharacter::OnSkillGimmickCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPOSGimmickInteractInterface* GimmickInteractInterface = Cast<IPOSGimmickInteractInterface>(OtherActor);
	if(GimmickInteractInterface)
	{
		GimmickInteractObjectList.Remove(GimmickInteractInterface);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APledgeOfStarlightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::Look);

		// Attack (Left Click)
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APledgeOfStarlightCharacter::AttackStarted);

		// UsePreset
		EnhancedInputComponent->BindAction(PresetActionList[1], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset1);
		EnhancedInputComponent->BindAction(PresetActionList[2], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset2);
		EnhancedInputComponent->BindAction(PresetActionList[3], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset3);
		EnhancedInputComponent->BindAction(PresetActionList[4], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset4);
		EnhancedInputComponent->BindAction(PresetActionList[5], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset5);
		EnhancedInputComponent->BindAction(PresetActionList[6], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset6);
		EnhancedInputComponent->BindAction(PresetActionList[7], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset7);
		EnhancedInputComponent->BindAction(PresetActionList[8], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset8);
		EnhancedInputComponent->BindAction(PresetActionList[9], ETriggerEvent::Triggered, this, &APledgeOfStarlightCharacter::RunPreset9);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APledgeOfStarlightCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APledgeOfStarlightCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APledgeOfStarlightCharacter::AttackStarted(const FInputActionValue& Value)
{
	if (ComboComponent)
	{
		ComboComponent->OnAttackInput();
	}
}

void APledgeOfStarlightCharacter::RunPreset1(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(1);
}

void APledgeOfStarlightCharacter::RunPreset2(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(2);
}

void APledgeOfStarlightCharacter::RunPreset3(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(3);
}

void APledgeOfStarlightCharacter::RunPreset4(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(4);
}

void APledgeOfStarlightCharacter::RunPreset5(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(5);
}

void APledgeOfStarlightCharacter::RunPreset6(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(6);
}

void APledgeOfStarlightCharacter::RunPreset7(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(7);
}

void APledgeOfStarlightCharacter::RunPreset8(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(8);
}

void APledgeOfStarlightCharacter::RunPreset9(const FInputActionValue& Value)
{
	PlayerAbility->UsePreset(9);
}

