// Fill out your copyright notice in the Description page of Project Settings.


#include "POSAttackIceHorming.h"
#include "Kismet/GameplayStatics.h"
#include "PledgeOfStarlight/Interface/POSEnemyInterface.h"

APOSAttackIceHorming::APOSAttackIceHorming()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;
	
	HitSearchArea = CreateDefaultSubobject<USphereComponent>(TEXT("HitSearchArea"));
	HitSearchArea->SetupAttachment(RootSceneComponent);
	HitSearchArea->SetSphereRadius(3200.0f);

	SkillID = ESkillID::Temp3;
	AttachPosition = FVector3d(0, 0, 160);
}

void APOSAttackIceHorming::BeginPlay()
{
	Super::BeginPlay();
	HitSearchArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InitTransform();

	HitSearchArea->OnComponentBeginOverlap.AddDynamic(this, &APOSAttackIceHorming::OnHitSearchCollisionOverlap);
	return;
}

void APOSAttackIceHorming::UseSkill()
{
	Super::UseSkill();
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation());
	SpawnTransform.SetRotation(GetActorRotation().Quaternion());
	SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	POSIceOrb = GetWorld()->SpawnActor<APOSIceOrb>(POSIceOrbClass, SpawnTransform);
	//부가요소는 부모에서부터 할당.
	POSIceOrb->SkillID = SkillID;
	POSIceOrb->HitFlash = HitFlash;

	UGameplayStatics::PlaySound2D(this, UsingSound);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Use Ice Orb"));
	}
	StartCollisionTrigger();
	return;
}

void APOSAttackIceHorming::StartCollisionTrigger()
{
	HitSearchArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APOSAttackIceHorming::EndCollisionTrigger, CollisionDuration, false);
	return;
}

void APOSAttackIceHorming::EndCollisionTrigger()
{
	HitSearchArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	return;
}

void APOSAttackIceHorming::OnHitSearchCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPOSEnemyInterface* POSEnemyInterface = Cast<IPOSEnemyInterface>(OtherActor);
	if(POSEnemyInterface)
	{
		POSIceOrb->ProjectileMovementComponent->HomingTargetComponent = POSEnemyInterface->GetHitPoint();
	}

	return;
}
