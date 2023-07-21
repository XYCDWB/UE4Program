// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"


void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//显示调试信息5秒
	//参数中的-1键 值类型参数能防止该消息被更新或刷新
	//游戏启动时，StartPlay()将在屏幕上打印一条新的调试消息（"Hello World, this is FPSGameModeBase!"），
	//采用黄色文本，显示五秒钟。
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World,this is UIGameMode!"));

}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void AMyGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget>NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

