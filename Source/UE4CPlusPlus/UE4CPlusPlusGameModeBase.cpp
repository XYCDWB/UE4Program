// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "UE4CPlusPlusGameModeBase.h"

void AUE4CPlusPlusGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//��ʾ������Ϣ5��
	//�����е�-1�� ֵ���Ͳ����ܷ�ֹ����Ϣ�����»�ˢ��
	//��Ϸ����ʱ��StartPlay()������Ļ�ϴ�ӡһ���µĵ�����Ϣ��"Hello World, this is FPSGameModeBase!"����
	//���û�ɫ�ı�����ʾ�����ӡ�
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World,this is FPSGameMode!"));

}
