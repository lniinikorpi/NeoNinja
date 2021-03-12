// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "GunBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = .2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	TurnLeftStick = false;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bNoFail = true;
	SpawnParameters.Owner = this;

	if (GetMesh()->GetSocketByName("Weapon_Spawn"))
	{
		FTransform GunSpawnTransform;
		FName WeaponSocket = "Weapon_Spawn";
		GunSpawnTransform.SetLocation(GetMesh()->GetSocketLocation(WeaponSocket));
		GunSpawnTransform.SetRotation(GetMesh()->GetSocketRotation(WeaponSocket).Quaternion());
		AGunBase* base = GetWorld()->SpawnActor<AGunBase>(SpawnedWeapon, GunSpawnTransform, SpawnParameters);
		if (base) {
			FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, false);
			base->AttachToComponent(GetMesh(), rules, WeaponSocket);
			//base->AttachToActor(this, rules);
		}
		CurrentWeapon = base;
	}
	
}

void APlayerCharacter::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void APlayerCharacter::RotateCharacter()
{
	// If no controller return
	if (Controller == nullptr)
	{
		return;
	}
	if (LookVector.IsZero())
	{
		if (!TurnLeftStick) {
			TurnLeftStick = true;
			//Mesh->SetRelativeRotation(FVector(0,-90,0).ToOrientationQuat());
			GetCharacterMovement()->bOrientRotationToMovement = true;
		}
	}
	else
	{
		TurnLeftStick = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		LookVector = Controller->GetControlRotation().Vector() - LookVector;
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(LookVector, Controller->GetControlRotation().Vector()));
		AddActorLocalRotation(FVector(0, 90, 0).ToOrientationQuat());
	}
}

void APlayerCharacter::GetRotX(float value) {
	LookVector.X = value;
}

void APlayerCharacter::GetRotY(float value) {
	LookVector.Y = value;
}

void APlayerCharacter::Shoot()
{
	CurrentWeapon->Shoot();
}

void APlayerCharacter::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateCharacter();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::GetRotX);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::GetRotY);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	/*PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);*/

}

