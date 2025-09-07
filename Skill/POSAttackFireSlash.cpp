// Fill out your copyright notice in the Description page of Project Settings.


#include "POSAttackFireSlash.h"
#include "Kismet/GameplayStatics.h"
#include "PledgeOfStarlight/Interface/POSEnemyInterface.h"

APOSAttackFireSlash::APOSAttackFireSlash()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	
	AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollision"));
	AttackCollision->SetupAttachment(RootComponent);
	AttackCollision->SetSphereRadius(200.0f);
	
	FireSlashEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_POSFireSlash"));
	FireSlashEffect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave> SoundAsset(TEXT("/Script/Engine.SoundWave'/Game/PledgeOfStarlight/Sound/Skill/SW_POSFireSlash.SW_POSFireSlash'"));
	if (SoundAsset.Succeeded())
	{
		UsingSound = SoundAsset.Object;
	}

	SkillID = ESkillID::FireSlash;
	AttachPosition = FVector(0,0,100);
	
}

void APOSAttackFireSlash::BeginPlay()
{
	Super::BeginPlay();
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &APOSAttackFireSlash::OnAttackCollisionOverlap);
	InitTransform();
	return;
}

void APOSAttackFireSlash::UseSkill() // 각종 데이터 SubSystem에서 가져오기
{
	Super::UseSkill();
	FireSlashEffect->SetActive(true, true);
	UGameplayStatics::PlaySound2D(this, UsingSound);

	PlayCollision();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Use Fire Slash"));
	}
	return;
	
}
void APOSAttackFireSlash::PlayCollision()
{
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, 
		this, 
		&APOSAttackFireSlash::OffCollision,  
		CollisionDuration,                   
		false                   
	);
	return;
}
void APOSAttackFireSlash::OffCollision()
{
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	return;
}

void APOSAttackFireSlash::OnAttackCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPOSEnemyInterface* POSEnemyInterface = Cast<IPOSEnemyInterface>(OtherActor);
	if(POSEnemyInterface)
	{
		HitEvent(OtherActor, SkillData.Damage, 0, POSEnemyInterface->GetHitPoint()->GetComponentLocation());
	}
	return;
}

