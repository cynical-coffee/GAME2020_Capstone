// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Cat_Lady.generated.h"

UCLASS()
class GAME2020_CAPSTONE_API ACat_Lady : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACat_Lady();

	UPROPERTY(BlueprintReadOnly)
	bool bIsAccelerating;
	/*UPROPERTY(EditAnywhere, Category = "Patrol Points", meta = (MakeEditWidget))
	FVector vPatrolPoint1;
	UPROPERTY(EditAnywhere, Category = "Patrol Points", meta = (MakeEditWidget))
	FVector vPatrolPoint2;
	UPROPERTY(EditAnywhere, Category = "Patrol Points", meta = (MakeEditWidget))
	FVector vPatrolPoint3;
	UPROPERTY(EditAnywhere, Category = "Patrol Points", meta = (MakeEditWidget))
	FVector vPatrolPoint4;*/
	UPROPERTY(EditAnywhere, Category = "Patrol Points", meta = (MakeEditWidget))
	TArray<FVector> arrLocalPatrolPoints;

	TArray<FVector> arrWorldPatrolPoints;



	/*TArray<FVector> arrPatrolPoints;*/
	int iCurrentPatrolIndex = 0;

	UFUNCTION(BlueprintCallable)
	void SetIsAccelerating(bool bAccelerating);
	UFUNCTION(BlueprintCallable)
	const FVector& GetNextPatrolLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
