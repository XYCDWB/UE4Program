// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//将该Pawn设置为最小编号玩家控制(默认玩家)
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//创建可附加内容的虚拟根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//创建相机和可见对象
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	//将相机和可见对象附加到根组件，偏移并旋转相机
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//根据"Grow"操作处理增长和减少
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing)
	{
		//一秒增长到两倍大小
		CurrentScale += DeltaTime;
	}
	else
	{
		//以增长速度缩减一半
		CurrentScale -= (DeltaTime * 0.5f);
	}

	//确保不会降至初始大小以下，或增至两倍大小以上
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));


	//根据 MoveForWard 和 MoveRight 处理移动
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//在按下或松开 "Grow"键 做出相应
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrow);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrow);

	//对两个移动轴的逐帧反应
	InputComponent->BindAxis("MoveForWard",this,&AMyPawn::MoveForWard);
	InputComponent->BindAxis("MoveRight",this,&AMyPawn::MoveRight);
}


//使用 FMath::Clamp 约束输入中得到的值，将其约束在-1到+1的范围内
void AMyPawn::MoveForWard(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::MoveRight(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrow()
{
	bGrowing = true;
}

void AMyPawn::StopGrow()
{
	bGrowing = false;
}

