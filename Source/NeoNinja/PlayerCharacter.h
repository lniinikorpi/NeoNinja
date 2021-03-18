// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GunBase.h"
#include "WeaponNode.h"
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
	UPROPERTY(EditAnywhere, Category = Weapon)
		TSubclassOf<class AWeaponNode> RevolverNode;
	UPROPERTY(EditAnywhere, Category = Weapon)
		TSubclassOf<class AWeaponNode> RifleNode;
	UPROPERTY(EditAnywhere, Category = Weapon)
		TSubclassOf<class AWeaponNode> ShotgunNode;



	AGunBase* CurrentWeapon;

	UFUNCTION()
		void Shoot();
	UFUNCTION()
		void UnShoot();
	UFUNCTION()
		void SetRifleNode();
	UFUNCTION()
		void SetRevolverNode();
	UFUNCTION()
		void SetShotgunNode();

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
