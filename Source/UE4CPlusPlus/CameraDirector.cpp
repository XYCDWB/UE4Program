// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
//GameplayStaticsͷ�ļ��������Ƿ���һЩ���õ�ͨ�ú���


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeToNextCameraChange -= DeltaTime;

	//�˴��뽫����������ÿ��3����������ͬ����������л�Ĭ����ҵ���ͼ��
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		//���Ҵ�������ҿ��Ƶ�actor
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this,0);
		if (OurPlayerController)
		{
			if (CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne))
			{
				//ƽ�����л��������2
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);				
			}
			else if (CameraOne)
			{				
				//�����л��������1
				OurPlayerController->SetViewTarget(CameraOne);
			}
		}
	}
}

