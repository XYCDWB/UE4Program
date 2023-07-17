// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProjectile.h"
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

	//FPS摄像机
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	//第一人称网格体(手臂)，仅对所属玩家可见
	UPROPERTY(VisibleDefaultsOnly,Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	//处理发射物射击的函数
	void Fire();


	//生成 FPSProjectile actor并实现 OnFire 函数时需要考虑两点，即：

	//发射物对应的类（让 FPSCharacter 及其派生蓝图知道要生成哪种发射物）。

	//将使用一个摄像机空间中的偏移向量来确定发射物的生成位置。
	//设置该参数为可编辑参数，这样可以在 BP_FPSCharacter 蓝图中对其进行设置和调整。
	//可以基于这些数据计算发射物的初始位置。
	//枪口相对于摄像机位置的偏移
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Gameplay)
	FVector MuzzleOffset;

	//要生成的发射物类
	UPROPERTY(EditDefaultsOnly,Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

};


