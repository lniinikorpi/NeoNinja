// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponNode.generated.h"

UCLASS()
class NEONINJA_API AWeaponNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponNode();
	UPROPERTY(EditAnywhere, Category = Stats)
		bool IsAutomatic;
	UPROPERTY(EditAnywhere, Category = Stats)
		float FireRateMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float RangeMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float AccuracyMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float DamageMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BulletSpeedMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BulletsPerShotMultiplier;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
