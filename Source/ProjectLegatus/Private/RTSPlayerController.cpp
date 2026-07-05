// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"

#include "EnhancedInputComponent.h"
#include "RTSCameraPawn.h"
#include "Engine/World.h"

#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(
			IA_MoveCamera,
			ETriggerEvent::Triggered,
			this,
			&ARTSPlayerController::MoveCamera
		);
	}
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller Started"));
	
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ARTSPlayerController::MoveCamera(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	
	if (ARTSCameraPawn* Camera = Cast<ARTSCameraPawn>(GetPawn()))
	{
		Camera->MoveCamera(Input, GetWorld()->GetDeltaSeconds());
	}
}
