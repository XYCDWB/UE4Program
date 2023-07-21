// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"


void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//��ʾ������Ϣ5��
	//�����е�-1�� ֵ���Ͳ����ܷ�ֹ����Ϣ�����»�ˢ��
	//��Ϸ����ʱ��StartPlay()������Ļ�ϴ�ӡһ���µĵ�����Ϣ��"Hello World, this is FPSGameModeBase!"����
	//���û�ɫ�ı�����ʾ�����ӡ�
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

