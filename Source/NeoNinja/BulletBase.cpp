// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletBase::ABulletBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = capsule;
	projectileMovement->UpdatedComponent = capsule;
	projectileMovement->InitialSpeed = 1000.f;
	projectileMovement->MaxSpeed = 1000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();

}

void ABulletBase::SetSpeed(float value) {
	BulletSpeedMultiplier = value;
	projectileMovement->MaxSpeed = projectileMovement->InitialSpeed * BulletSpeedMultiplier;

	projectileMovement->Velocity *= BulletSpeedMultiplier;
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

