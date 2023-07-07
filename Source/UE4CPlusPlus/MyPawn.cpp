// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//����Pawn����Ϊ��С�����ҿ���(Ĭ�����)
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//�����ɸ������ݵ���������
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//��������Ϳɼ�����
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	//������Ϳɼ����󸽼ӵ��������ƫ�Ʋ���ת���
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

	//����"Grow"�������������ͼ���
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing)
	{
		//һ��������������С
		CurrentScale += DeltaTime;
	}
	else
	{
		//�������ٶ�����һ��
		CurrentScale -= (DeltaTime * 0.5f);
	}

	//ȷ�����ή����ʼ��С���£�������������С����
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));


	//���� MoveForWard �� MoveRight �����ƶ�
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

	//�ڰ��»��ɿ� "Grow"�� ������Ӧ
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrow);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrow);

	//�������ƶ������֡��Ӧ
	InputComponent->BindAxis("MoveForWard",this,&AMyPawn::MoveForWard);
	InputComponent->BindAxis("MoveRight",this,&AMyPawn::MoveRight);
}


//ʹ�� FMath::Clamp Լ�������еõ���ֵ������Լ����-1��+1�ķ�Χ��
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

