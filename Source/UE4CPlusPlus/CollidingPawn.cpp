// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"
#include "CollidingPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���������Ϊ����Ӧ������
	USphereComponent* SphereComponet = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponet;
	SphereComponet->InitSphereRadius(40.0f);
	SphereComponet->SetCollisionProfileName(TEXT("Pawn"));

	//���� ��̬������ ��Դ���������Ӱ뾶Ϊ50�Ŀɼ����塣
	//����ղŴ����İ뾶40����������޷���ȫ�Ǻϣ�����轫������С80%�����轫�������ƶ�40��λ��ʹ��������������������Ķ���
	//����������������������Ա�鿴����λ��
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}


	//���ǻ�Ծ����ϵͳ������ӵ��㼶��
	//���ڴ����в��ݴ������Ȼ������������п��ء�
	//ע�⣺����ϵͳ���ֱ�Ӹ��ӵ���̬��������������Ǹ��ӵ�������ͬʱ��΢ƫ��������ײ����ģ��Ա�������ʱ������ʾ
	//�����ɼ����ֹͣ������ϵͳ
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	//ָ��·��
	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	//���õ��ɱ�������ɽ�������Ե�����׷��Pawn���ٶȼ��ٺͼ��٣��Ӷ���ø�ƽ������������ӵ㡣
	//��ͬʱӵ�����ù��ܣ��ɷ�ֹ�������������������ڴ���������ڵ����˳���Ϸ���˵�����ʱ�������
	//��Ȼ���ɱ�������Ǳ�Ҫ������������ܹ����������������Ϸ���ƶ�ʱ��ø���ƽ����
	//ʹ�õ��ɱ۸��������ƽ����Ȼ���˶���
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// ��������������ӵ����ɱ�
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// ����Ĭ�����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//�����ƶ������ʵ������Ҫ������¸�
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;


}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ParticelToggle",IE_Pressed,this,&ACollidingPawn::ParticleToggle);

	InputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("MoveRight",this,&ACollidingPawn::MoveRight);
	InputComponent->BindAxis("CameraYaw",this,&ACollidingPawn::CameraYaw);
	InputComponent->BindAxis("CameraPitch", this, &ACollidingPawn::CameraPitch);
}

UPawnMovementComponent * ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::CameraYaw(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::CameraPitch(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}

