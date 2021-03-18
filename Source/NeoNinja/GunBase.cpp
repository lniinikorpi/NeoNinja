// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "WeaponNode.h"

// Sets default values
AGunBase::AGunBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	isFiring = false;
	BaseFireRate = 1;
	BaseRange = .5;
	BaseAccuracy = 2;
	BaseDamage = 1;
	BaseBulletSpeed = 1.f;
	BaseBulletsPerShot = 1;
	BaseIsAutomatic = false;
	ResetNodes();

}

void AGunBase::Shoot()
{
	isFiring = true;
}

void AGunBase::SetNode(TSubclassOf<AWeaponNode> node)
{
	if (WeaponNodes.Num() >= 2) {
		WeaponNodes.Empty();
		ResetNodes();
	}
	else {
		WeaponNodes.Add(node);
		AWeaponNode* wn = GetWorld()->SpawnActor<AWeaponNode>(node);
		GetNodeValues(wn);
		wn->Destroy();
		
	}
}

void AGunBase::UnShoot() {
	isFiring = false;
}

void AGunBase::FireWeapon() {
	//CurrentIsAutomatic = IfAutomatic();
	if (CurrentIsAutomatic) {
		SpawnProjectile();
	}
	else {
		SpawnProjectile();
		UnShoot();
	}
}

void AGunBase::SpawnProjectile() {
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bNoFail = true;
	SpawnParameters.Owner = this;
	if (Mesh->GetSocketByName("Muzzle"))
	{
		for (int i = 0; i < CurrentBulletsPerShot; i++)
		{
			FTransform BulletSpawnTransform;
			BulletSpawnTransform.SetLocation(Mesh->GetSocketLocation("Muzzle"));
			FQuat rotation = Mesh->GetSocketRotation("Muzzle").Quaternion();
			if (i > 0)
			{
				rotation = rotation - FQuat(0,0,FMath::Pow(-1,i) * FMath::DegreesToRadians(15),0);
			}
			float sway = FMath::RandRange(-CurrentAccuracy, CurrentAccuracy);
			rotation = rotation + FQuat(0,0,FMath::DegreesToRadians(sway),0);
			BulletSpawnTransform.SetRotation(rotation);
			rotation.Y = 0;
			BulletSpawnTransform.SetRotation(rotation);
			ABulletBase* spawnedBullet = GetWorld()->SpawnActor<ABulletBase>(bullet, BulletSpawnTransform, SpawnParameters);
			SetBulletValues(spawnedBullet);
		}
	}
}

void AGunBase::SetBulletValues(ABulletBase* b) {
	b->SetSpeed(CurrentBulletSpeed);
	b->SetLifeSpan(CurrentRange);
}

bool AGunBase::IfAutomatic() {
	bool isAutomatic = false;
	for (int i = 0; i < WeaponNodes.Num(); i++)
	{
		AWeaponNode* node = GetWorld()->SpawnActor<AWeaponNode>(WeaponNodes[i]);
		if (node->IsAutomatic) {
			isAutomatic = true;
		}
		node->Destroy();
	}
	return isAutomatic;
}

void AGunBase::GetNodeValues(AWeaponNode* node) {
	CurrentAccuracy += node->AccuracyMultiplier;
	CurrentBulletSpeed *= node->BulletSpeedMultiplier;
	CurrentBulletsPerShot *= node->BulletsPerShotMultiplier;
	CurrentDamage *= node->DamageMultiplier;
	CurrentFireRate *= node->FireRateMultiplier;
	CurrentRange *= node->RangeMultiplier;
	if (!CurrentIsAutomatic)
	{
		CurrentIsAutomatic = node->IsAutomatic;
	}
}

void AGunBase::ResetNodes() {
	CurrentFireRate = BaseFireRate;
	CurrentRange = BaseRange;
	CurrentAccuracy = BaseAccuracy;
	CurrentDamage = BaseDamage;
	CurrentBulletSpeed = BaseBulletSpeed;
	CurrentBulletsPerShot = BaseBulletsPerShot;
	CurrentIsAutomatic = BaseIsAutomatic;
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isFiring)
	{
		if (GetGameTimeSinceCreation() > canFire) {
			canFire = GetGameTimeSinceCreation() + 1 / CurrentFireRate;
			FireWeapon();
		}
	}

}

