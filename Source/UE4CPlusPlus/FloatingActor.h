// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class UE4CPLUSPLUS_API AFloatingActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	//声明StaticMeshComponent，它将担当对象的视觉表示。
	//请注意，它使用 UProperty 宏，这使它在虚幻编辑器中可见。
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	//添加变量来控制它的行为
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "FloaingActor")
	float FloatSpeed=20.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "FloaingActor")
	float RotationSpeed=20.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	


};
