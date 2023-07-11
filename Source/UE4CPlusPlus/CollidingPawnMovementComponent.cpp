// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//确保所有事物持续有效，以便进行移动
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//该代码将在场景中平滑移动Pawn，适当时在表面滑动。未对Pawn应用重力，其最大速度被硬编码为每秒150 虚幻单位

	//此 TickComponent 函数使用 UPawnMovementComponent 类提供的几种强大功能。

	//	ConsumeInputVector 报告并清空用于存储移动输入的内置变量值。

	//	SafeMoveUpdatedComponent 利用虚幻引擎物理移动Pawn移动组件，同时考虑固体障碍。

	//	移动导致碰撞时， SlideAlongSurface 会处理沿墙壁和斜坡等碰撞表面平滑滑动所涉及的计算和物理，而非直接停留原地，粘在墙壁或斜坡上。

	//	Pawn移动组件中还包含众多值得探究的功能，但本教程范围中暂时无需使用。可查看如 浮动Pawn移动、旁观者Pawn移动 或 **角色移动组件**等其他类，了解额外使用范例和方法。


	//获取(然后清除)ACollidingPawn::Tick中设置的移动向量
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//若发生碰撞，尝试滑过去
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}