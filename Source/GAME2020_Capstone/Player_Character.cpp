// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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

	GetCapsuleComponent()->SetCapsuleHalfHeight(30.0);
	GetCapsuleComponent()->SetCapsuleRadius(30.0);

	GetMesh()->SetRelativeLocation(FVector(-10.0, 0.0, -32.0));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Spring Arm
	mThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	mThirdPersonSpringArm->SetupAttachment(RootComponent);
	const FRotator rSpringArmRotation(-30.0, 0.0, 0.0);
	//mThirdPersonSpringArm->SetRelativeRotation(rSpringArmRotation);
	mThirdPersonSpringArm->bUsePawnControlRotation = true;
	const FVector mThirdPersonSpringOffset(0.0, 0.0, 250.0);
	mThirdPersonSpringArm->SocketOffset = mThirdPersonSpringOffset;

	// Third-Person Camera
	mThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	mThirdPersonCamera->SetupAttachment(mThirdPersonSpringArm, USpringArmComponent::SocketName);
	mThirdPersonCamera->bUsePawnControlRotation = false;
	const FRotator mCameraRotation(-30.0, 0.0, 0.0);
	mThirdPersonCamera->SetRelativeRotation(mCameraRotation);


	// Player movement values
	GetCharacterMovement()->MaxWalkSpeed = 250;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->JumpZVelocity = 700.0f;

	// Jump count
	iJumpCount = 0;
	bIsRunning = false;
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

void APlayer_Character::ToggleRun()
{
	if (!bIsRunning)
	{
		GetCharacterMovement()->MaxWalkSpeed = 700;
		bIsRunning = true;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Running")));
	}
	else if (bIsRunning)
	{
		GetCharacterMovement()->MaxWalkSpeed = 250;
		bIsRunning = false;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Walking")));
	}

}

void APlayer_Character::Jump()
{
	Super::Jump();
	JumpMaxCount = 2;
	iJumpCount++;
	if (iJumpCount == 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Double Jump")));
		
	}
	/*const FVector vLaunchVel(0.0, 0.0, 800.0);
	if (iJumpCount == 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Double Jump")));
		LaunchCharacter(vLaunchVel, false, false);
	}*/
}

void APlayer_Character::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	iJumpCount = 0;
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

	// Toggle Run
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayer_Character::ToggleRun);

	// Jump bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_Character::Jump);

	// Camera bindings
	PlayerInputComponent->BindAxis("Turn", this, &APlayer_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_Character::AddControllerPitchInput);
}

bool APlayer_Character::GetRunningFlag()
{
	return bIsRunning;
}

int APlayer_Character::GetJumpCount()
{
	return iJumpCount;
}
