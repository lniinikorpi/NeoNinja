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
	UPROPERTY(EditAnywhere, Category = Bullet)
		UProjectileMovementComponent* projectileMovement;
	UPROPERTY(EditAnywhere, Category = Bullet)
		UCapsuleComponent* capsule;
	void SetSpeed(float value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float BulletSpeedMultiplier;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
