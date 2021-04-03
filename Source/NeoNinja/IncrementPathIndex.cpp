// Fill out your copyright notice in the Description page of Project Settings.


#include "IncrementPathIndex.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy.h"
#include "blackboard_keys.h"
#include "BehaviorTree/BlackboardComponent.h"

UIncrementPathIndex::UIncrementPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get the ai controller
	ANPC_AIController* const Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	AEnemy* Enemy = Cast<AEnemy>(Controller->GetPawn());
	int const NoOfPoints = Enemy->GetPatrolPath()->Num();
	int const MinIndex = 0;
	int const MaxIndex = NoOfPoints - 1;

	//get and set the black board index key
	int Index = Controller->Get_Blackboard()->GetValueAsInt(bb_keys::patrol_path_index);
	if(Index >= MaxIndex && Direction == EDirectionType::Forward)
	{
		Direction = EDirectionType::Reverse;
	}
	else if(Index == MinIndex && Direction == EDirectionType::Reverse)
	{
		Direction = EDirectionType::Forward;
	}
	Controller->Get_Blackboard()->SetValueAsInt(bb_keys::patrol_path_index,
		(Direction == EDirectionType::Forward ? ++Index : --Index) % NoOfPoints);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
