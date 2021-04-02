// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "PlayerCharacter.generated.h"

USTRUCT()
struct FGunNode {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Stats)
		float AmmoUsageMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		bool IsAutomatic;
	UPROPERTY(EditAnywhere, Category = Stats)
		float FireRateMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float RangeMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float AccuracyMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float DamageMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BulletSpeedMultiplier;
	UPROPERTY(EditAnywhere, Category = Stats)
		float BulletsPerShotMultiplier;
};

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
	
	UPROPERTY(EditAnywhere, Category = Gun_Nodes)
		FGunNode RifleNode;
	UPROPERTY(EditAnywhere, Category = Gun_Nodes)
		FGunNode ShotgunNode;
	UPROPERTY(EditAnywhere, Category = Gun_Nodes)
		FGunNode RevolverNode;


	UPROPERTY(BlueprintReadOnly)
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
private:
	class UAIPerceptionStimuliSourceComponent* Stimulus;

	void Setup_Stimulus();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
