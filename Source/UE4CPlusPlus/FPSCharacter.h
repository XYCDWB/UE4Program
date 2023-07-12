// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class UE4CPLUSPLUS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//前后移动
	UFUNCTION()
	void MoveForWard(float AxisValue);
	
	//左右移动
	UFUNCTION()
	void MoveRight(float AxisValue);

	//按下键时，设置跳跃标记
	UFUNCTION()
	void StartJump();

	//释放按键，清除跳跃标记
	UFUNCTION()
	void StopJump();

};
