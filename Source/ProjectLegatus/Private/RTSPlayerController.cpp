// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"

#include "EnhancedInputComponent.h"
#include "RTSCameraPawn.h"
#include "Engine/World.h"

#include "EnhancedInputSubsystems.h"
#include "RTSCommandManager.h"
#include "RTSSelectionManager.h"
#include "RTSUnit.h"
#include "Core/RTSCollisionChannels.h"
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
		// Movement
		EnhancedInput->BindAction(
			IA_MoveCamera,
			ETriggerEvent::Triggered,
			this,
			&ARTSPlayerController::MoveCamera
		);
		
		EnhancedInput->BindAction(
			IA_MoveCamera,
			ETriggerEvent::Completed,
			this,
			&ARTSPlayerController::MoveCamera
		);
		
		EnhancedInput->BindAction(
			IA_MoveCamera,
			ETriggerEvent::Canceled,
			this,
			&ARTSPlayerController::MoveCamera
		);
		
		// Zoom
		EnhancedInput->BindAction(
			IA_ZoomCamera,
			ETriggerEvent::Triggered,
			this,
			&ARTSPlayerController::ZoomCamera
		);
		
		// Rotation
		EnhancedInput->BindAction(
			IA_RotateCamera,
			ETriggerEvent::Triggered,
			this,
			&ARTSPlayerController::RotateCamera
		);
		
		EnhancedInput->BindAction(
			IA_RotateCamera,
			ETriggerEvent::Completed,
			this,
			&ARTSPlayerController::RotateCamera
		);
		
		EnhancedInput->BindAction(
			IA_RotateCamera,
			ETriggerEvent::Canceled,
			this,
			&ARTSPlayerController::RotateCamera
		);
		
		// mouse 
		EnhancedInput->BindAction(
			IA_Select,
			ETriggerEvent::Started,
			this,
			&ARTSPlayerController::HandleSelection
		);
		
		EnhancedInput->BindAction(
			IA_Command,
			ETriggerEvent::Started,
			this,
			&ARTSPlayerController::HandleCommand
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
	const FVector2D Input = Value.Get<FVector2D>();
	
	if (ARTSCameraPawn* Camera = Cast<ARTSCameraPawn>(GetPawn()))
	{
		Camera->MoveCamera(Input);
	}
}

void ARTSPlayerController::ZoomCamera(const FInputActionValue& Value)
{
	const float Input = Value.Get<float>();
	
	if (ARTSCameraPawn* Camera = Cast<ARTSCameraPawn>(GetPawn()))
	{
		Camera->ZoomCamera(Input);
	}
}

void ARTSPlayerController::RotateCamera(const FInputActionValue& Value)
{
	const float Input = Value.Get<float>();
	
	if (ARTSCameraPawn* Camera = Cast<ARTSCameraPawn>(GetPawn()))
	{
		Camera->RotateCamera(Input);
	}
}

void ARTSPlayerController::HandleSelection()
{
	URTSSelectionManager* SelectionManager = GetWorld()->GetSubsystem<URTSSelectionManager>();
	if (!SelectionManager) return;
	
	FHitResult HitResult;
	
	bool bHit = GetHitResultUnderCursorByChannel(
		UEngineTypes::ConvertToTraceType(RTSCollisionChannels::UnitSelection),
		false,
		HitResult
	);
	
	if (bHit)
	{
		if (ARTSUnit* Unit = Cast<ARTSUnit>(HitResult.GetActor()))
		{
			SelectionManager->SelectUnit(Unit);
		}
	}
	else
	{
		SelectionManager->ClearSelection();
	}
}

void ARTSPlayerController::HandleCommand()
{
	URTSSelectionManager* SelectionManager = GetWorld()->GetSubsystem<URTSSelectionManager>();

	URTSCommandManager* CommandManager = GetWorld()->GetSubsystem<URTSCommandManager>();

	if (!SelectionManager || !CommandManager) return;
	
	FHitResult HitResult;
	
	bool bHit = GetHitResultUnderCursorByChannel(
		UEngineTypes::ConvertToTraceType(RTSCollisionChannels::GroundSelection),
		false,
		HitResult
	);
	if (!bHit) return;
	
	ARTSUnit* SelectedUnit = SelectionManager->GetSelectedUnit();
	if (!SelectedUnit) return;
	
	CommandManager->IssueMoveCommand(SelectedUnit, HitResult.Location);
}
