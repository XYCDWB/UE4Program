// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//此函数是 构造函数，它在类首次创建时告诉该类如何初始化自身。
	//我们添加的代码将会在VisualMesh引用中填充新的StaticMeshComponent、 将它附加到Actor，
	//并将它设为 初学者内容包 资源中的立方体模型。

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));


	if (CubeVisualAsset.Succeeded())
	{

		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	}

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//将使立方体在上下浮动的同时旋转。
	FVector  NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;        //按FloatSpeed调整高度
	float DeltaRotation = DeltaTime * RotationSpeed;  //每秒旋转等于RotationSpeed的角度
	NewRotation.Roll += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
	


	
}

