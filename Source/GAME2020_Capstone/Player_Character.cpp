// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayer_Character::APlayer_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Prevent player from moving with controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Game assigns player to character controller player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// player can receive input
	AutoReceiveInput = EAutoReceiveInput::Player0;

	// Spring Arm
	mThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	mThirdPersonSpringArm->SetupAttachment(RootComponent);
	const FRotator rSpringArmRotation(-30.0, 0.0, 0.0);
	mThirdPersonSpringArm->SetRelativeRotation(rSpringArmRotation);
	mThirdPersonSpringArm->bUsePawnControlRotation = true;

	// Third-Person Camera
	mThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	mThirdPersonCamera->SetupAttachment(mThirdPersonSpringArm, USpringArmComponent::SocketName);
	mThirdPersonCamera->bUsePawnControlRotation = false;

	// Player movement values
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
}

// Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMax = 30;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMin = 330;
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

void APlayer_Character::Jump()
{
	Super::Jump();
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

	// Jump bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayer_Character::StopJumping);

	// Camera bindings
	PlayerInputComponent->BindAxis("Turn", this, &APlayer_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_Character::AddControllerPitchInput);
}