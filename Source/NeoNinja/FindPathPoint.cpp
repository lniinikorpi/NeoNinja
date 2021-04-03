// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPathPoint.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy.h"
#include "blackboard_keys.h"
#include "BehaviorTree/Tasks/BTTask_FinishWithResult.h"

UFindPathPoint::UFindPathPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("FInd Patrol Path Point");
}

EBTNodeResult::Type UFindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get the ai controller
	ANPC_AIController* const Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());

	//get current patrol path index from blackboard
	int const Index = Controller->Get_Blackboard()->GetValueAsInt(bb_keys::patrol_path_index);

	//use the index to get the current patrol path from the enemy
	AEnemy* const Enemy = Cast<AEnemy>(Controller->GetPawn());
	FVector const Point = Enemy->GetPatrolPath()->GetPatrolPoint(Index);
	
	 //transform the point to global position
	FVector const GlobalPoint = Enemy->GetPatrolPath()->GetActorTransform().TransformPosition(Point);

	//write the global point to the blackboard
	Controller->Get_Blackboard()->SetValueAsVector(bb_keys::control_path_vector, GlobalPoint);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
