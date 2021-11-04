// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayer_Character::APlayer_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	mThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Third Person SpringArm"));
	mThirdPersonSpringArm->SetupAttachment(RootComponent);
	const FRotator rSpringArmRotation(-30.0, 0.0, 0.0);
	mThirdPersonSpringArm->SetRelativeRotation(rSpringArmRotation);

	mThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	mThirdPersonCamera->SetupAttachment(mThirdPersonSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	
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

}

