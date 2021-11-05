// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME2020_CAPSTONE_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;
	// Animation Properties
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties();

public:
	// Character Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APawn* OwningPawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayer_Character* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAccelerating;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsRunning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDoubleJumping;


};
