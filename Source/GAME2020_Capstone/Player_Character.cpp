// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayer_Character::APlayer_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Game assigns player to character controller player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// player can receive input
	AutoReceiveInput = EAutoReceiveInput::Player0;

	// Spring Arm
	mThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Third Person SpringArm"));
	mThirdPersonSpringArm->SetupAttachment(RootComponent);
	const FRotator rSpringArmRotation(-30.0, 0.0, 0.0);
	mThirdPersonSpringArm->SetRelativeRotation(rSpringArmRotation);

	// Third-Person Camera
	mThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	mThirdPersonCamera->SetupAttachment(mThirdPersonSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayer_Character::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator rRotation = Controller->GetControlRotation();
		const FRotator rYawRotation(0.0, rRotation.Yaw, 0);
		const FVector vDirection = FRotationMatrix(rYawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(vDirection, value);
	}
}

void APlayer_Character::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator rRotation = Controller->GetControlRotation();
		const FRotator rYawRotation(0.0, rRotation.Yaw, 0);
		const FVector vDirection = FRotationMatrix(rYawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(vDirection, value);
	}
}

// Called every frame
void APlayer_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayer_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_Character::MoveRight);
}