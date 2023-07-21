// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4CPLUSPLUS_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		
		virtual void StartPlay() override;

public:
	// �Ƴ���ǰ�˵��ؼ�������ָ����(����)���½��ؼ�
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget>NewWidgetClass);

protected:
	//��Ϸ��ʼʱ����
	virtual void BeginPlay() override;

	//��Ϸ��ʼʱ�������˵��Ŀؼ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget>StartingWidgetClass;

	//�����˵��Ŀؼ�ʵ��
	UPROPERTY()
		UUserWidget* CurrentWidget;


	
};
