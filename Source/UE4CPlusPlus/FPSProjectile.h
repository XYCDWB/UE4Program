// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class UE4CPLUSPLUS_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//球体碰撞组件
	UPROPERTY(VisibleDefaultsOnly,Category = Projectile)
	USphereComponent* CollisionComponent;

	//发射物移动组件
	UPROPERTY(VisibleAnywhere,Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	//初始化射击方向上发射物速度的函数
	void FireInDirection(const FVector& ShootDirection);


};


