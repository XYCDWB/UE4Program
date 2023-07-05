// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class UE4CPLUSPLUS_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY ��ʹ�ñ����� ������� �ɼ���
	//������������Ϸ���ڽ����Ĺ����Ự����������ؿ�����Ŀʱ����Щ���������õ�ֵ�����ᱻ���á�
	//EditAnywhere �ؼ��֣����������� ��ñ༭�� �����������1��CameraOne���������2��CameraTwo����
	UPROPERTY(EditAnywhere)
	AActor* CameraOne;

	UPROPERTY(EditAnywhere)
	AActor* CameraTwo;

	float TimeToNextCameraChange;

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

};
