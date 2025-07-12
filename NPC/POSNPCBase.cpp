// Fill out your copyright notice in the Description page of Project Settings.


#include "POSNPCBase.h"

#include "POSNPCGameInstanceSubSystem.h"
#include "PledgeOfStarlight/Interface/POSPlayerInterface.h"

// Sets default values
APOSNPCBase::APOSNPCBase()
{
	DialogueTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTrigger"));
	DialogueTrigger->SetupAttachment(RootComponent);
	DialogueTrigger->SetSphereRadius(150.0f);
	DialogueTrigger->SetCollisionProfileName(TEXT("Dialogue"));
	
	DialogueBuilderObject = CreateDefaultSubobject<UDialogueBuilderObject>(TEXT("DialogueBuilderObject"));
}

void APOSNPCBase::InteractSkill(FName SkillID)
{
	for (auto Element : NPCInfo.SkillGimmickDataList)
	{
		if(Element.SkillID == SkillID)
		{
			if(Element.isRepeatable || !GimmickExecutionMap[SkillID])
			{
				UE_LOG(LogTemp, Log, TEXT("Play Skill Gimmick : %s "), *SkillID.ToString())
				//TODO : 실행 부분. -> 실행 부분에 GimmickExecutionMap true로 변경.
				GimmickSuccessMap[SkillID] = true;
				break;
			}
		}
	}
}

// Called when the game starts or when spawned
void APOSNPCBase::BeginPlay()
{
	Super::BeginPlay();

	UPOSNPCGameInstanceSubSystem* NPCSubSystem = GetGameInstance()->GetSubsystem<UPOSNPCGameInstanceSubSystem>();
	if(NPCSubSystem)
	{
		NPCInfo = NPCSubSystem->GetNPCData(NPCID);
	}
	InitGimmickMap();
	DialogueTrigger->OnComponentBeginOverlap.AddDynamic(this, &APOSNPCBase::OnDialogueCollisionBeginOverlap);
	DialogueTrigger->OnComponentEndOverlap.AddDynamic(this, &APOSNPCBase::OnDialogueCollisionEndOverlap);
	
	return;
}

void APOSNPCBase::InitGimmickMap()
{
	if(isSaved)
	{
		return;
	}
	for (auto SkillGimmickData : NPCInfo.SkillGimmickDataList)
	{
		GimmickSuccessMap.Add(SkillGimmickData.SkillID, false);
		GimmickExecutionMap.Add(SkillGimmickData.SkillID, false);
	}
	isSaved = true;
	//TODO : Save
}

void APOSNPCBase::OnDialogueCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPOSPlayerInterface* PlayerInterface = Cast<IPOSPlayerInterface>(OtherActor);
	if(PlayerInterface)
	{
		if(!PlayerInterface->GetNPCDialogueHighlightWidget())
		{
			NPCDialogueHighlightWidgetInstance = CreateWidget<UPOSNPCDialogueHighlightWidget>(GetWorld(), NPCDialogueHighlightWidget);
			NPCDialogueHighlightWidgetInstance->DialogueContent = DialogueBuilderObject;
			PlayerInterface->SetNPCDialogueHighlightWidget(NPCDialogueHighlightWidgetInstance);
			NPCDialogueHighlightWidgetInstance->AddToViewport();
		}
	}
	return;
}

void APOSNPCBase::OnDialogueCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPOSPlayerInterface* PlayerInterface = Cast<IPOSPlayerInterface>(OtherActor);
	if(PlayerInterface)
	{
		if(PlayerInterface->GetNPCDialogueHighlightWidget())
		{
			PlayerInterface->SetNPCDialogueHighlightWidget(nullptr);
			NPCDialogueHighlightWidgetInstance->RemoveFromParent();
		}
	}
	return;
}