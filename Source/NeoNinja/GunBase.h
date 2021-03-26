// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.h"
#include "PlayerCharacter.h"
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
	UPROPERTY(BlueprintReadOnly, Category = Stats, meta = (ToolTip = "Rounds per second"))
		float BaseFireRate;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseRange;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseAccuracy;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseDamage;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseBulletSpeed;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseBulletsPerShot;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		bool BaseIsAutomatic;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseAmmoUsage;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float AmmoRechargeDelay;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float CurrentAmmo;
		float MaxAmmo;
		float AmmoRechargeRate;

	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> PlayerAmmoWidgetBP;
		UUserWidget* PlayerAmmoWidget;

	float canFire;
	bool isFiring;

	void FireWeapon();
	void SpawnProjectile();
	void UnShoot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetBulletValues(ABulletBase* b);
	bool IfAutomatic();
	void GetNodeValues(FGunNode node);
	void ResetNodes();
	void RechargeAmmo();
	float CurrentFireRate;
	float CurrentRange;
	float CurrentAccuracy;
	float CurrentDamage;
	float CurrentBulletSpeed;
	float CurrentBulletsPerShot;
	bool CurrentIsAutomatic;
	float CurrentAmmoUsage;
	float CanRecharge;
	TArray<FGunNode> WeaponNodes;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Shoot();
	void SetNode(FGunNode node);

};
