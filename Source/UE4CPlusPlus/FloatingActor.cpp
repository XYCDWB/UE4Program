// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//�˺����� ���캯�����������״δ���ʱ���߸�����γ�ʼ������
	//������ӵĴ��뽫����VisualMesh����������µ�StaticMeshComponent�� �������ӵ�Actor��
	//��������Ϊ ��ѧ�����ݰ� ��Դ�е�������ģ�͡�

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

	//��ʹ�����������¸�����ͬʱ��ת��
	FVector  NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;        //��FloatSpeed�����߶�
	float DeltaRotation = DeltaTime * RotationSpeed;  //ÿ����ת����RotationSpeed�ĽǶ�
	NewRotation.Roll += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
	


	
}

