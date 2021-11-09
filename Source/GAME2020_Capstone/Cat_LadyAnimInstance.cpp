// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat_LadyAnimInstance.h"

#include "Cat_Lady.h"

void UCat_LadyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningPawn == nullptr)
	{
		OwningPawn = TryGetPawnOwner();
		if (OwningPawn)
		{
			mCatLady = Cast<ACat_Lady>(OwningPawn);
		}
	}
}

void UCat_LadyAnimInstance::UpdateAnimationProperties()
{
	if (OwningPawn == nullptr)
	{
		OwningPawn = TryGetPawnOwner();
	}

	if (mCatLady)
	{
		bIsAccelerating = mCatLady->bIsAccelerating;
	}
	else
	{
		mCatLady = Cast<ACat_Lady>(OwningPawn);
		if (mCatLady)
		{
			bIsAccelerating = mCatLady->bIsAccelerating;
		}
	}
}
