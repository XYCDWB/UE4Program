// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//ȷ���������������Ч���Ա�����ƶ�
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//�ô��뽫�ڳ�����ƽ���ƶ�Pawn���ʵ�ʱ�ڱ��滬����δ��PawnӦ��������������ٶȱ�Ӳ����Ϊÿ��150 ��õ�λ

	//�� TickComponent ����ʹ�� UPawnMovementComponent ���ṩ�ļ���ǿ���ܡ�

	//	ConsumeInputVector ���沢������ڴ洢�ƶ���������ñ���ֵ��

	//	SafeMoveUpdatedComponent ����������������ƶ�Pawn�ƶ������ͬʱ���ǹ����ϰ���

	//	�ƶ�������ײʱ�� SlideAlongSurface �ᴦ����ǽ�ں�б�µ���ײ����ƽ���������漰�ļ������������ֱ��ͣ��ԭ�أ�ճ��ǽ�ڻ�б���ϡ�

	//	Pawn�ƶ�����л������ڶ�ֵ��̽���Ĺ��ܣ������̷̳�Χ����ʱ����ʹ�á��ɲ鿴�� ����Pawn�ƶ����Թ���Pawn�ƶ� �� **��ɫ�ƶ����**�������࣬�˽����ʹ�÷����ͷ�����


	//��ȡ(Ȼ�����)ACollidingPawn::Tick�����õ��ƶ�����
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//��������ײ�����Ի���ȥ
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}