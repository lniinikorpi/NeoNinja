// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BulletBase.generated.h"

UCLASS()
class NEONINJA_API ABulletBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABulletBase();
	/*UPROPERTY(VisibleAnywhere, Category = Bullet)
		UStaticMeshComponent* mesh;*/
	UPROPERTY(EditAnywhere, Category = Projectile)
		UProjectileMovementComponent* projectileMovement;
	UPROPERTY(EditAnywhere, Category = Projectile)
		UCapsuleComponent* capsule;
	void SetSpeed(float value);

	UFUNCTION()
		void OnHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float BulletSpeedMultiplier;

};
