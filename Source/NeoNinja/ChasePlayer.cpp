// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"

UChasePlayer::UChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = (TEXT("Chase Player"));
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get target location from blackboard
	ANPC_AIController* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	FVector const playerLocation = cont->Get_Blackboard()->GetValueAsVector(bb_keys::target_location);

	//move to players location
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, playerLocation);

	//finish with success
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
