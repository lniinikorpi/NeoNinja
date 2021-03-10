// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

// Sets default values
AGunBase::AGunBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

}

void AGunBase::Shoot()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bNoFail = true;
	SpawnParameters.Owner = this;

	FTransform BulletSpawnTransform;
	if (Mesh->GetSocketByName("Muzzle"))
	{
		BulletSpawnTransform.SetLocation(Mesh->GetSocketLocation("Muzzle"));
		BulletSpawnTransform.SetRotation(Mesh->GetSocketRotation("Muzzle").Quaternion());
		ABulletBase* base = GetWorld()->SpawnActor<ABulletBase>(bullet, BulletSpawnTransform, SpawnParameters);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Mesh->GetSocketLocation("Muzzle").ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *base->K2_GetActorLocation().ToString());
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

}

