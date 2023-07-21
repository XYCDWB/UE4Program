// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UE4CPlusPlusGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4CPLUSPLUS_API AUE4CPlusPlusGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};
