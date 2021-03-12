// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "GameFramework/Actor.h"

// Sets default values
AGunBase::AGunBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	isFiring = false;
	FireRate = 3;

}

void AGunBase::Shoot()
{
	isFiring = true;
}

void AGunBase::UnShoot() {
	isFiring = false;
}

void AGunBase::FireWeapon() {

	if (IsAutomatic) {
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
		FTransform BulletSpawnTransform;
		BulletSpawnTransform.SetLocation(Mesh->GetSocketLocation("Muzzle"));
		FQuat rotation = Mesh->GetSocketRotation("Muzzle").Quaternion();
		rotation.X = 0;
		BulletSpawnTransform.SetRotation(rotation);
		ABulletBase* base = GetWorld()->SpawnActor<ABulletBase>(bullet, BulletSpawnTransform, SpawnParameters);
	}
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
			canFire = GetGameTimeSinceCreation() + 1 / FireRate;
			FireWeapon();
		}
	}

}

