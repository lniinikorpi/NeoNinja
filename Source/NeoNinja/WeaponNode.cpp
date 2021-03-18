// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponNode.h"

// Sets default values
AWeaponNode::AWeaponNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	IsAutomatic = false;
	FireRateMultiplier = 1.f;
	RangeMultiplier = 1.f;
	AccuracyMultiplier = 1.f;
	DamageMultiplier = 1.f;
	BulletSpeedMultiplier = 1.f;
	BulletsPerShotMultiplier = 1.f;

}

// Called when the game starts or when spawned
void AWeaponNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

