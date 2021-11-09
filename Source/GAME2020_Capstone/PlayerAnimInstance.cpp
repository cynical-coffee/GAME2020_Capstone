// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "Player_Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningPawn == nullptr)
	{
		OwningPawn = TryGetPawnOwner();
		if (OwningPawn)
		{
			PlayerCharacter = Cast<APlayer_Character>(OwningPawn);
		}
	}
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	if (OwningPawn == nullptr)
	{
		OwningPawn = TryGetPawnOwner();
	}

	if (OwningPawn)
	{
		// Check if player exists
		if (PlayerCharacter == nullptr)
		{
			PlayerCharacter = Cast<APlayer_Character>(OwningPawn);
		}

		// Check if player is accelerating
		if (PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		// Check if player is running
		if (!PlayerCharacter->GetRunningFlag())
		{
			bIsRunning = false;
		}
		else if (PlayerCharacter->GetRunningFlag())
		{
			bIsRunning = true;
		}

		// Check if player is in the air 
		if (PlayerCharacter->GetCharacterMovement()->IsFalling())
		{
			bIsInAir = true;
		}
		else
		{
			bIsInAir = false;
		}

		// Checks if the player is jumping
		if (PlayerCharacter->GetJumpCount() > 1)
		{
			bIsDoubleJumping = true;
		}
		else
		{
			bIsDoubleJumping = false;
		}

		// Check if the player is falling
		if (PlayerCharacter->GetVelocity().Z < 0)
		{
			bIsFallingDown = true;
		}
		else
		{
			bIsFallingDown = false;
		}
	}
}
