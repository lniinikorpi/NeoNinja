// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& Object_Initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> OBJ(TEXT("BehaviorTree'/Game/Blueprints/AI/Enemy_BT.Enemy_BT'"));
	if(OBJ.Succeeded())
	{
		BehaviorTree = OBJ.Object;
	}
	BehaviorTreeComponent = Object_Initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviourComponent"));
	BlackboardComponent = Object_Initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	SetupPerceptionSystem();
}

void ANPC_AIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void ANPC_AIController::OnPossess(APawn* const IPawn)
{
	Super::OnPossess(IPawn);
	if(BlackboardComponent)
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* ANPC_AIController::Get_Blackboard() const
{
	return BlackboardComponent;
}

void ANPC_AIController::On_Target_Detected(AActor* actor, FAIStimulus const Stimulus)
{
	if(auto const ch = Cast<APlayerCharacter>(actor))
	{
		Get_Blackboard()->SetValueAsBool(bb_keys::can_see_player, Stimulus.WasSuccessfullySensed());
	}
}

void ANPC_AIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//add sight configuration component to perception component
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_AIController::On_Target_Detected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
