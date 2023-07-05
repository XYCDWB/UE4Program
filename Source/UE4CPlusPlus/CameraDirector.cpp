// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
//GameplayStatics头文件允许我们访问一些有用的通用函数


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

	//此代码将可以让我们每隔3秒在两个不同的摄像机间切换默认玩家的视图。
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		//查找处理本地玩家控制的actor
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this,0);
		if (OurPlayerController)
		{
			if (CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne))
			{
				//平缓地切换到摄像机2
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);				
			}
			else if (CameraOne)
			{				
				//立即切换到摄像机1
				OurPlayerController->SetViewTarget(CameraOne);
			}
		}
	}
}

