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

	//����StaticMeshComponent����������������Ӿ���ʾ��
	//��ע�⣬��ʹ�� UProperty �꣬��ʹ������ñ༭���пɼ���
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	//��ӱ���������������Ϊ
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
