// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"
#include "Engine/Canvas.h"

void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		//找出画布中心点
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		//偏移纹理大小的一半，以便纹理中心与画布中心对齐
		FVector2D CrosshairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

		//在中心点绘制十字准星
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}
