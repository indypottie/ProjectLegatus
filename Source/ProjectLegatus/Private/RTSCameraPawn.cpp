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
	
	// configure SpringArm
	SpringArm->TargetArmLength = 2200.f;
	SpringArm->SetRelativeRotation(FRotator(-55.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = false;
	
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

}

// Called to bind functionality to input
void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARTSCameraPawn::MoveCamera(const FVector2D& Input, float DeltaTime)
{
	if (Input.IsNearlyZero()) return;
	
	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	
	Forward.Z = 0.f;
	Right.Z = 0.f;
	
	Forward.Normalize();
	Right.Normalize();
	
	FVector Movement = Forward * Input.Y + Right * Input.X;
	
	SetActorLocation(GetActorLocation() + Movement * Settings.MoveSpeed * DeltaTime);
}

