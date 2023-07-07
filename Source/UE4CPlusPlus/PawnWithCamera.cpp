// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���Ǵ�����һ�� SceneComponent ��Ϊ��ǰ ��� �㼶�ĸ��ڵ㣬Ȼ���������������һ�� StaticMeshComponent��
	//֮�������ִ�����һ�� SpringArmComponent ��һ�� ����� ��������ҽ����������󶨵��˵��ɱ�ĩ�˵Ĳ���ϡ����ɱ۵�Ĭ�ϽǶȱ�����Ϊ-60�ȣ�����λ�ڸ��ڵ��Ϸ�50��λ��
	//���ǻ�Ϊ SpringArmComponent ������һЩ�����������������ĳ��Ⱥ��ƶ�ƽ���̶�

	//�������
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//�����
	staticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(staticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//ΪSpringArm��ı�����ֵ
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	//����Ĭ�����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();	
}


//ʹ�� Tick �����е���Щֵ��ÿ֡���� Pawn �� Camera
// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��������˷Ŵ�ť��Ŵ󣬷������С
	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;     //Zoom in over half a second
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;	//Zoom out over a quarter of a second
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	//����ZoomFactor���������������Ұ��SpringArm�ĳ���
	CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);

	//��תActor��ƫת�Ƕȣ������������Actor�໥�󶨣���������Ҳ��ƫת
	FRotator NewActorRotation = GetActorRotation();
	NewActorRotation.Yaw += CameraInput.X;
	SetActorRotation(NewActorRotation);

	//��ת������ĸ����Ƕȣ�������������ƣ�ȷ��ʼ�ճ��¿�
	FRotator NewCameraRotation = SpringArmComp->GetComponentRotation();
	NewCameraRotation.Pitch = FMath::Clamp(NewCameraRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
	SpringArmComp->SetWorldRotation(NewCameraRotation);

	//����"MoveX"��"MoveY"�����ƶ�
	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal() * 200.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

//��Pawn�������¼��ͺ������
// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//��ZoomIn�¼�
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn",IE_Released,this,&APawnWithCamera::ZoomOut);

	//Ϊ��������¼�(ÿ֡����)
	InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);


}


//���뺯��
void APawnWithCamera::MoveForward(float AxisValue) 
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue) 
{
	CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut() 
{
	bZoomingIn = false;
}





