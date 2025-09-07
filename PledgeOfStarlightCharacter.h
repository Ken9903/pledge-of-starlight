// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/POSPlayerInterface.h"
#include "Logging/LogMacros.h"
#include "Player/POSPlayerAbility.h"
#include "Player/POSPlayerInventory.h"
#include "Components/SphereComponent.h"
#include "Interface/POSGimmickInteractInterface.h"
#include "Player/POSComboComponent.h"
#include "PledgeOfStarlightCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APledgeOfStarlightCharacter : public ACharacter, public IPOSPlayerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Gimmick", EditDefaultsOnly)
	TArray<IPOSGimmickInteractInterface*> GimmickInteractObjectList;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	//Custom Player Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = POS_Ability, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPOSPlayerAbility> PlayerAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = POS_Inventory, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPOSPlayerInventory> PlayerInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = POS_Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPOSComboComponent> ComboComponent;

	UPROPERTY(Category = "POS|Collision", EditDefaultsOnly)
	TObjectPtr<USphereComponent> SkillGimmickTrigger;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Attack Input Action (Left Click) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TArray<UInputAction*> PresetActionList;

	

public:
	APledgeOfStarlightCharacter();

	UFUNCTION(Category = "POS|Player")
	virtual UPOSPlayerAbility* GetPlayerAbility() override;

	UFUNCTION(Category = "POS|Player")
	virtual UPOSPlayerInventory* GetPlayerInventory() override;

	//Dialogue
	UFUNCTION(Category = "POS|Player")
	virtual UPOSNPCDialogueHighlightWidget* GetNPCDialogueHighlightWidget() override;
	UFUNCTION(Category = "POS|Player")
	virtual void SetNPCDialogueHighlightWidget(UPOSNPCDialogueHighlightWidget* InNPCDialogueHighlightWidget) override;

protected:
	//Dialogue
	UPROPERTY(Category = "POS|Scenario", EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPOSNPCDialogueHighlightWidget> NPCDialogueHighlightWidget = nullptr; //기본 nullptr상태, Dialogue Trigger시 할당.

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void AttackStarted(const FInputActionValue& Value);

	void RunPreset0(const FInputActionValue& Value);
	void RunPreset1(const FInputActionValue& Value);
	void RunPreset2(const FInputActionValue& Value);
	void RunPreset3(const FInputActionValue& Value);
	void RunPreset4(const FInputActionValue& Value);
	void RunPreset5(const FInputActionValue& Value);
	void RunPreset6(const FInputActionValue& Value);
	void RunPreset7(const FInputActionValue& Value);
	void RunPreset8(const FInputActionValue& Value);
	void RunPreset9(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	UFUNCTION(Category = "POS|Gimmick")
	void OnSkillGimmickCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(Category = "POS|Gimmick")
	void OnSkillGimmickCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};

