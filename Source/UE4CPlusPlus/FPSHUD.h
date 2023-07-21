// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE4CPLUSPLUS_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	

public:
	//HUD���Ƶ���Ҫ����
	virtual void DrawHUD() override;

protected:
	//������������Ļ����
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;



};
