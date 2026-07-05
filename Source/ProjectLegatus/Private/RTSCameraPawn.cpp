// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARTSCameraPawn::ARTSCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	// configure SpringArm and related variables
	SpringArm->TargetArmLength = 2200.f;
	SpringArm->SetRelativeRotation(FRotator(-55.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = false;
	TargetZoom = SpringArm->TargetArmLength;
	
	// configure Camera
	Camera->bUsePawnControlRotation = false;
	
	// disable pawn rotation
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Camera Pawn Spawned"));
}

// Called every frame
void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// update camera input
	HandleMovement(DeltaTime);
	HandleRotation(DeltaTime);
	HandleZoom(DeltaTime);
}

void ARTSCameraPawn::MoveCamera(const FVector2D& Input)
{
	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	
	Forward.Z = 0.f;
	Right.Z = 0.f;
	
	Forward.Normalize();
	Right.Normalize();
	
	MovementInput = Forward * Input.Y + Right * Input.X;
}

void ARTSCameraPawn::ZoomCamera(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		TargetZoom -= Value * Settings.ZoomSpeed;
		TargetZoom = FMath::Clamp(TargetZoom, Settings.MinZoom, Settings.MaxZoom);
	}
}

void ARTSCameraPawn::RotateCamera(float Value)
{
	RotationInput = Value;
}

void ARTSCameraPawn::HandleMovement(float DeltaTime)
{
	if (MovementInput.IsNearlyZero()) return;
	SetActorLocation(GetActorLocation() + MovementInput * Settings.MoveSpeed * DeltaTime);
}

void ARTSCameraPawn::HandleRotation(float DeltaTime)
{
	if (FMath::IsNearlyZero(RotationInput)) return;
	AddActorWorldRotation(FRotator(0.f, RotationInput * Settings.RotationSpeed * DeltaTime, 0.f));
}

void ARTSCameraPawn::HandleZoom(float DeltaTime)
{
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetZoom, DeltaTime, 8.f);
}