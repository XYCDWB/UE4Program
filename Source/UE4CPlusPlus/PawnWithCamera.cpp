// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//我们创建了一个 SceneComponent 作为当前 组件 层级的根节点，然后在它下面添加了一个 StaticMeshComponent。
	//之后，我们又创建了一个 SpringArmComponent 和一个 摄像机 组件，并且将摄像机组件绑定到了弹簧臂末端的插槽上。弹簧臂的默认角度被设置为-60度，并且位于根节点上方50单位。
	//我们还为 SpringArmComponent 声明了一些变量，用于设置它的长度和移动平滑程度

	//创建组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//绑定组件
	staticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(staticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//为SpringArm类的变量赋值
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	//控制默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();	
}


//使用 Tick 函数中的这些值来每帧更新 Pawn 和 Camera
// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//如果按下了放大按钮则放大，否则就缩小
	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;     //Zoom in over half a second
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;	//Zoom out over a quarter of a second
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	//根据ZoomFactor来设置摄像机的视野和SpringArm的长度
	CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);

	//旋转Actor的偏转角度，由于摄像机与Actor相互绑定，因此摄像机也会偏转
	FRotator NewActorRotation = GetActorRotation();
	NewActorRotation.Yaw += CameraInput.X;
	SetActorRotation(NewActorRotation);

	//旋转摄像机的俯仰角度，但对其进行限制，确保始终朝下看
	FRotator NewCameraRotation = SpringArmComp->GetComponentRotation();
	NewCameraRotation.Pitch = FMath::Clamp(NewCameraRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
	SpringArmComp->SetWorldRotation(NewCameraRotation);

	//根据"MoveX"和"MoveY"处理移动
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

//把Pawn的输入事件和函数相绑定
// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//绑定ZoomIn事件
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn",IE_Released,this,&APawnWithCamera::ZoomOut);

	//为四条轴绑定事件(每帧调用)
	InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);


}


//输入函数
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





