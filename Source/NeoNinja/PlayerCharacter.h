// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GunBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class NEONINJA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	UPROPERTY(EditAnywhere, Category = Camera)
		class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, Category = Camera)
		class UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		float BaseLookUpRate;
	UPROPERTY(EditAnywhere, Category = Weapon)
		TSubclassOf<class AGunBase> SpawnedWeapon;

	AGunBase* CurrentWeapon;

	UFUNCTION()
		void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void TurnAtRate(float rate);
	void LookUpAtRate(float rate);
	void RotateCharacter();
	void GetRotX(float value);
	void GetRotY(float value);
	FVector LookVector;
	FVector RotVector;
	bool TurnLeftStick;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
