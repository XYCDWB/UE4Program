// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建第一人称摄像机组件
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	//将摄像机组件附加到胶囊体组件
	//创建 UCameraComponent，并将其附加到角色的 CapsuleComponent
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent,UCapsuleComponent>(GetCapsuleComponent()));

	//将摄像机置于略高于眼睛上方的位置
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f,0.0f,50.0f+BaseEyeHeight));

	//启用Pawn控制摄像机旋转
	FPSCameraComponent->bUsePawnControlRotation = true;

	//为所属玩家创建第一人称网格体组件
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	//SetOnlyOwnerSee 表示此网格体仅对拥有此角色的 PlayerController 可见。
	//此代码还将网格体附加到摄像机，并禁用某些环境阴影。让手臂投射阴影会破坏第一人称角色应该只有单个网格体的感觉
	//仅所属玩家可以看见此网格体
	FPSMesh->SetOnlyOwnerSee(true);

	//将FPS网格体附加到FPS摄像机
	FPSMesh->SetupAttachment(FPSCameraComponent);

	//禁用某些环境阴影以便实现只有单个网格体的感觉
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//所属玩家看不到常规(第三人称)全身网格体
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	if (GEngine)
	{
		// 显示调试消息五秒。 
		// -1"键"值参数可以防止更新或刷新消息。
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

	//绑定移动
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForWard);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	//绑定视角旋转和俯仰
	PlayerInputComponent->BindAxis("CameraYaw", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch",this,&AFPSCharacter::AddControllerPitchInput);

	//设置跳跃绑定
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this,&AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&AFPSCharacter::StopJump);

	//绑定开火
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForWard(float AxisValue)
{
	//找出玩家“前进”方向，并记录玩家想向该方向移动
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::MoveRight(float AxisValue)
{
	//找出玩家“右侧”方向，并记录玩家想向该方向移动
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
	//试图发射发射物
	if (ProjectileClass)
	{
		//获取摄像机变换
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		
		//设置MuzzOffset，在略靠近摄像机前生成发射物
		MuzzleOffset.Set(100.0f,0.0f,0.0f);

		//将MuzzleOffset从摄像机空间变换到世界空间
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		//使目标方向略向上倾斜
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld * world = GetWorld();
		if (world)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//在枪口的位置生成发射物
			AFPSProjectile* Projectile = world->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				//设置发射物的初始轨迹
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}


}

