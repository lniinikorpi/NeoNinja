// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "BehaviorTree//BehaviorTreeComponent.h"
#include "BehaviorTree//BehaviorTree.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "UObject//ConstructorHelpers.h"
#include "PlayerCharacter.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& Object_Initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> OBJ(TEXT("BehaviorTree'/Game/Blueprints/AI/Enemy_BT.Enemy_BT'"));
	if(OBJ.Succeeded())
	{
		BehaviorTree = OBJ.Object;
	}
	BehaviorTreeComponent = Object_Initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviourComponent"));
	BlackboardComponent = Object_Initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
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
