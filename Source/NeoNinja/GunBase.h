// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.h"
#include "WeaponNode.h"
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
	UPROPERTY(EditAnywhere, Category = Stats, meta = (ToolTip = "Rounds per second"))
		float BaseFireRate;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BaseRange;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BaseAccuracy;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BaseDamage;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BaseBulletSpeed;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BaseBulletsPerShot;
	UPROPERTY(EditAnywhere, Category = Stats)
		bool BaseIsAutomatic;

	float canFire;
	bool isFiring;

	void FireWeapon();
	void SpawnProjectile();
	void UnShoot();

	UPROPERTY(EditAnywhere, Category = Stats)
		TArray<TSubclassOf<AWeaponNode>> WeaponNodes;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetBulletValues(ABulletBase* b);
	bool IfAutomatic();
	void GetNodeValues(AWeaponNode* node);
	void ResetNodes();
	float CurrentFireRate;
	float CurrentRange;
	float CurrentAccuracy;
	float CurrentDamage;
	float CurrentBulletSpeed;
	float CurrentBulletsPerShot;
	bool CurrentIsAutomatic;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Shoot();
	void SetNode(TSubclassOf<AWeaponNode> node);

};
