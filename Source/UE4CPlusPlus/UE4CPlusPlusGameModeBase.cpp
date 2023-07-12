// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "UE4CPlusPlusGameModeBase.h"

void AUE4CPlusPlusGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//显示调试信息5秒
	//参数中的-1键 值类型参数能防止该消息被更新或刷新
	//游戏启动时，StartPlay()将在屏幕上打印一条新的调试消息（"Hello World, this is FPSGameModeBase!"），
	//采用黄色文本，显示五秒钟。
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World,this is FPSGameMode!"));

}
