// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Cat_LadyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME2020_CAPSTONE_API UCat_LadyAnimInstance : public UAnimInstance
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
	class ACat_Lady* mCatLady;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAccelerating;
	
};
