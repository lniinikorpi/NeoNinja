// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABulletBase::ABulletBase()
{
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	capsule->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	capsule->CanCharacterStepUpOn = ECB_No;
	RootComponent = capsule;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
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
	capsule->BodyInstance.SetCollisionProfileName("Projectile");
	capsule->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);

}

void ABulletBase::SetSpeed(float value) {
	BulletSpeedMultiplier = value;
	projectileMovement->MaxSpeed = projectileMovement->InitialSpeed * BulletSpeedMultiplier;

	projectileMovement->Velocity *= BulletSpeedMultiplier;
}

void ABulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("moro"));
	if(!OtherActor->ActorHasTag("Bullet"))
	{
		Destroy();
	}
}

