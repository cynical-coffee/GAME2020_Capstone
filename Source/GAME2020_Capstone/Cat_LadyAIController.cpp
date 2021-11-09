// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat_LadyAIController.h"

#include "Cat_Lady.h"
#include "NavigationSystem.h"

void ACat_LadyAIController::BeginPlay()
{
	Super::BeginPlay();

	//GoToRandomWaypoint();
	//GetWorld()->GetTimerManager().SetTimer(mTimerHandle, this, &ACat_LadyAIController::GoToRandomWaypoint, 3, false);

	GetWorld()->GetTimerManager().SetTimer(mTimerHandle, this, &ACat_LadyAIController::GoToNextPatrolPoint, 3, false);
}

void ACat_LadyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//GoToRandomWaypoint();

	ACat_Lady* mControllingEnemy = Cast<ACat_Lady>(GetPawn());
	if (mControllingEnemy)
	{
		mControllingEnemy->SetIsAccelerating(false);
	}
	//GetWorld()->GetTimerManager().SetTimer(mTimerHandle, this, &ACat_LadyAIController::GoToRandomWaypoint, 3, false);
	GetWorld()->GetTimerManager().SetTimer(mTimerHandle, this, &ACat_LadyAIController::GoToNextPatrolPoint, 3, false);
}

void ACat_LadyAIController::GoToRandomWaypoint()
{
	APawn* mControllingPawn = GetPawn();
	if (mControllingPawn)
	{
		UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavigationSystem)
		{
			FVector mResult;
			bool bSuccess = NavigationSystem->K2_GetRandomPointInNavigableRadius(GetWorld(), mControllingPawn->GetActorLocation(), mResult, 3000);
			if (bSuccess)
			{
				MoveToLocation(mResult);
				ACat_Lady* mControllingEnemy = Cast<ACat_Lady>(mControllingPawn);
				if (mControllingEnemy)
				{
					mControllingEnemy->SetIsAccelerating(true);
				}
			}
		}
	}
}

void ACat_LadyAIController::GoToNextPatrolPoint()
{
	ACat_Lady* mControllingEnemy = Cast<ACat_Lady>(GetPawn());
	if (mControllingEnemy)
	{
		MoveToLocation(mControllingEnemy->GetNextPatrolLocation());
		mControllingEnemy->SetIsAccelerating(true);
	}
}
