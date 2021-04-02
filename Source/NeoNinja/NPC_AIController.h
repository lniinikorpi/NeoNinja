// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class NEONINJA_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()
	public:
		ANPC_AIController(FObjectInitializer const& Object_Initializer = FObjectInitializer::Get());
		void BeginPlay() override;
		void OnPossess(APawn* const IPawn) override;
		class UBlackboardComponent* Get_Blackboard() const;
	private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackboardComponent;
};
