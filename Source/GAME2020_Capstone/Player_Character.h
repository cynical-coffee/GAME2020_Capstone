// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Character.generated.h"

UCLASS()
class GAME2020_CAPSTONE_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* mThirdPersonSpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* mThirdPersonCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float value);
	void MoveRight(float value);

public:
	// Sets default values for this character's properties
	APlayer_Character();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
