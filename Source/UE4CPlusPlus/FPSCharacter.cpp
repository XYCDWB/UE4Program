// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//������һ�˳���������
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	//�������������ӵ����������
	//���� UCameraComponent�������丽�ӵ���ɫ�� CapsuleComponent
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent,UCapsuleComponent>(GetCapsuleComponent()));

	//������������Ը����۾��Ϸ���λ��
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f,0.0f,50.0f+BaseEyeHeight));

	//����Pawn�����������ת
	FPSCameraComponent->bUsePawnControlRotation = true;

	//Ϊ������Ҵ�����һ�˳����������
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	//SetOnlyOwnerSee ��ʾ�����������ӵ�д˽�ɫ�� PlayerController �ɼ���
	//�˴��뻹�������帽�ӵ��������������ĳЩ������Ӱ�����ֱ�Ͷ����Ӱ���ƻ���һ�˳ƽ�ɫӦ��ֻ�е���������ĸо�
	//��������ҿ��Կ�����������
	FPSMesh->SetOnlyOwnerSee(true);

	//��FPS�����帽�ӵ�FPS�����
	FPSMesh->SetupAttachment(FPSCameraComponent);

	//����ĳЩ������Ӱ�Ա�ʵ��ֻ�е���������ĸо�
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//������ҿ���������(�����˳�)ȫ��������
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	if (GEngine)
	{
		// ��ʾ������Ϣ���롣 
		// -1"��"ֵ�������Է�ֹ���»�ˢ����Ϣ��
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//���ƶ�
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForWard);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	//���ӽ���ת�͸���
	PlayerInputComponent->BindAxis("CameraYaw", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch",this,&AFPSCharacter::AddControllerPitchInput);

	//������Ծ��
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this,&AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&AFPSCharacter::StopJump);

	//�󶨿���
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForWard(float AxisValue)
{
	//�ҳ���ҡ�ǰ�������򣬲���¼�������÷����ƶ�
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::MoveRight(float AxisValue)
{
	//�ҳ���ҡ��Ҳࡱ���򣬲���¼�������÷����ƶ�
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	//��ͼ���䷢����
	if (ProjectileClass)
	{
		//��ȡ������任
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		
		//����MuzzOffset�����Կ��������ǰ���ɷ�����
		MuzzleOffset.Set(100.0f,0.0f,0.0f);

		//��MuzzleOffset��������ռ�任������ռ�
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		//ʹĿ�귽����������б
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld * world = GetWorld();
		if (world)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//��ǹ�ڵ�λ�����ɷ�����
			AFPSProjectile* Projectile = world->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				//���÷�����ĳ�ʼ�켣
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}


}

