#include "Cat_Lady.h"

// Sets default values
ACat_Lady::ACat_Lady()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACat_Lady::SetIsAccelerating(bool bAccelerating)
{
	bIsAccelerating = bAccelerating;
}

const FVector& ACat_Lady::GetNextPatrolLocation()
{
	if (arrWorldPatrolPoints.Num() > 0)
	{
		++iCurrentPatrolIndex;
		if (iCurrentPatrolIndex >= arrWorldPatrolPoints.Num())
		{
			iCurrentPatrolIndex = 0;
		}
		return arrWorldPatrolPoints[iCurrentPatrolIndex];
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("error")));
		return FVector::ZeroVector;
	}

	//++iCurrentPatrolIndex;
	/*if (iCurrentPatrolIndex >= arrPatrolPoints.Num())
	{
		iCurrentPatrolIndex = 0;
	}
	return arrPatrolPoints[iCurrentPatrolIndex];*/
}

// Called when the game starts or when spawned
void ACat_Lady::BeginPlay()
{
	Super::BeginPlay();
	/*arrPatrolPoints.Add(vPatrolPoint1 + GetActorLocation());
	arrPatrolPoints.Add(vPatrolPoint2 + GetActorLocation());
	arrPatrolPoints.Add(vPatrolPoint3 + GetActorLocation());
	arrPatrolPoints.Add(vPatrolPoint4 + GetActorLocation());*/

	arrWorldPatrolPoints.Add(GetActorLocation());
	for (FVector PatrolPoint : arrLocalPatrolPoints)
	{
		arrWorldPatrolPoints.Add(PatrolPoint + GetActorLocation());
	}
}

// Called every frame
void ACat_Lady::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAccelerating)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("true")));
	}
	else if (bIsAccelerating == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("false")));
	}
}
