// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.h"
#include "GunBase.generated.h"

UCLASS()
class NEONINJA_API AGunBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunBase();
	UPROPERTY(EditAnywhere, Category = Components)
		class USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = Components)
		TSubclassOf<class ABulletBase> bullet;
	UPROPERTY(EditAnywhere, Category = Stats)
		bool IsAutomatic;
	UPROPERTY(EditAnywhere, Category = Stats, meta = (ToolTip = "Rounds per second"))
		float FireRate;

	float canFire;
	bool isFiring;

	void FireWeapon();
	void SpawnProjectile();
	void UnShoot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Shoot();

};
