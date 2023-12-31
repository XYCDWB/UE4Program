// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class UE4CPLUSPLUS_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* OurCamera;

	//四个输入函数将被绑定到输入事件。其运行时，将对新输入变量中存储的值进行更新，
	//MyPawn将使用此类值决定游戏期间应执行的操作
	void MoveForWard(float AxisValue);
	void MoveRight(float AxisValue);
	void StartGrow();
	void StopGrow();

	FVector CurrentVelocity;
	bool bGrowing;

};
