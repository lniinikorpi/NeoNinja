// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NPC_AIController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboard_keys.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get AI controller and its NPC
	auto const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	auto const npc = cont->GetPawn();

	//Obtain npc location to use as an origin location
	FVector const origin = npc->GetActorLocation();
	FNavLocation loc;

	//get the navigation system and generate a random location on the NavMesh
	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	if(nav_sys->GetRandomPointInNavigableRadius(origin, SearchRadius, loc, nullptr))
	{
		cont->Get_Blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
	}

	//finish with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
