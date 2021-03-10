// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BulletBase.generated.h"

UCLASS()
class NEONINJA_API ABulletBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABulletBase();
	UPROPERTY(VisibleAnywhere, Category = Bullet)
		UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere, Category = Bullet)
		UProjectileMovementComponent* projectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};