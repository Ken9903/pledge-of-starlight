// Fill out your copyright notice in the Description page of Project Settings.


#include "POSIceOrb.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "PledgeOfStarlight/Interface/POSEnemyInterface.h"

APOSIceOrb::APOSIceOrb()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollision"));
	RootComponent = AttackCollision;
	RootComponent->SetMobility(EComponentMobility::Movable);
	
	IceOrbNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("IceOrbNiagaraComponent"));
	IceOrbNiagaraComponent->SetupAttachment(AttackCollision);
	IceOrbNiagaraComponent->SetMobility(EComponentMobility::Movable);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
}

void APOSIceOrb::BeginPlay()
{
	Super::BeginPlay();
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &APOSIceOrb::OnAttackCollisionOverlap);
	GetWorld()->GetTimerManager().SetTimer(StartTimerHandle, this, &APOSIceOrb::StartChasing, ChasingDelay, false);
}

void APOSIceOrb::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(StartTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(DestroyTimerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
}

void APOSIceOrb::StartChasing()
{
	ProjectileMovementComponent->Velocity = FVector3d(0, 0, 0);
	ProjectileMovementComponent->bIsHomingProjectile = true;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &APOSIceOrb::DestroyIceOrbActor, LifeTime, false);
}

void APOSIceOrb::DestroyIceOrbActor()
{
	Super::Destroy();
	if (IsValid(this))
	{
		this->ConditionalBeginDestroy();
	}
}

void APOSIceOrb::OnAttackCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPOSEnemyInterface* POSEnemyInterface = Cast<IPOSEnemyInterface>(OtherActor);
	if(POSEnemyInterface)
	{
		HitEvent(OtherActor, SkillData.Damage, 0, GetActorLocation());
		AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &APOSIceOrb::DestroyIceOrbActor);	
	}
	return;
}
