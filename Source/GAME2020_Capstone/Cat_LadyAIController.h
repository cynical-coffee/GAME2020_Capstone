// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Cat_LadyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME2020_CAPSTONE_API ACat_LadyAIController : public AAIController
{
	GENERATED_BODY()

private:

	FTimerHandle mTimerHandle;

protected:

	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UFUNCTION()
	void GoToRandomWaypoint();
	UFUNCTION()
	void GoToNextPatrolPoint();
};
