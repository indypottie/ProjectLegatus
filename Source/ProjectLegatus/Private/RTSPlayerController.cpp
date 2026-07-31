// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"

#include "EnhancedInputComponent.h"
#include "RTSCameraPawn.h"
#include "Engine/World.h"

#include "EnhancedInputSubsystems.h"
#include "RTSCommandManager.h"
#include "RTSSelectionManager.h"
#include "RTSUnit.h"
#include "SelectionBoxWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Core/RTSCollisionChannels.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

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
			IA_Command,
			ETriggerEvent::Started,
			this,
			&ARTSPlayerController::HandleCommand
		);
		
		EnhancedInput->BindAction(
			IA_Select,
			ETriggerEvent::Started,
			this,
			&ARTSPlayerController::BeginSelection
		);

		EnhancedInput->BindAction(
			IA_Select,
			ETriggerEvent::Triggered,
			this,
			&ARTSPlayerController::UpdateSelection
		);

		EnhancedInput->BindAction(
			IA_Select,
			ETriggerEvent::Completed,
			this,
			&ARTSPlayerController::EndSelection
		);
	}
}

void ARTSPlayerController::SetSelectionWidget(USelectionBoxWidget* Widget)
{
	SelectionWidget = Widget;
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
	
	ERTSSelectionMode SelectionMode = ERTSSelectionMode::Replace;
	
	if (bHit)
	{
		if (ARTSUnit* Unit = Cast<ARTSUnit>(HitResult.GetActor()))
		{
			if (IsInputKeyDown(EKeys::LeftShift))
			{
				SelectionMode = ERTSSelectionMode::Add;
			}
			else if (IsInputKeyDown(EKeys::LeftControl))
			{
				SelectionMode = ERTSSelectionMode::Toggle;
			}
			
			SelectionManager->Select(Unit, SelectionMode);
		}
	}
	else
	{
		if (SelectionMode == ERTSSelectionMode::Replace)
		{
			SelectionManager->ClearSelection();
		}
	}
}

void ARTSPlayerController::HandleBoxSelection()
{
	// temporary way to get actors TODO: when player manager or something similar has been implemented that spawns units change this
	TArray<AActor*> Units;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ARTSUnit::StaticClass(),
		Units
	);
	
	const FVector2D Min(
		FMath::Min(SelectionStart.X, SelectionEnd.X),
		FMath::Min(SelectionStart.Y, SelectionEnd.Y)
	);

	const FVector2D Max(
		FMath::Max(SelectionStart.X, SelectionEnd.X),
		FMath::Max(SelectionStart.Y, SelectionEnd.Y)
	);
	
	TArray<ARTSUnit*> SelectedUnits;
	for (auto& Unit : Units)
	{
		FVector2D ScreenPosition;
		ProjectWorldLocationToScreen(Unit->GetActorLocation(), ScreenPosition);
		
		const bool bInsideX = ScreenPosition.X >= Min.X && ScreenPosition.X <= Max.X;
		const bool bInsideY = ScreenPosition.Y >= Min.Y && ScreenPosition.Y <= Max.Y;
		
		if (bInsideX && bInsideY)
		{
			SelectedUnits.Add(Cast<ARTSUnit>(Unit));
		}
	}

	URTSSelectionManager* SelectionManager = GetWorld()->GetSubsystem<URTSSelectionManager>();
	if (!SelectionManager) return;
	
	SelectionManager->Select(SelectedUnits, ERTSSelectionMode::Replace);
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
	
	CommandManager->IssueMoveCommand(SelectionManager->GetSelectedUnits(), HitResult.Location);
}

void ARTSPlayerController::BeginSelection()
{
	if (!SelectionWidget) return;
	
	GetMousePosition(SelectionStart.X, SelectionStart.Y);
	SelectionEnd = SelectionStart;
}

void ARTSPlayerController::UpdateSelection()
{
	if (!SelectionWidget) return;
	
	GetMousePosition(SelectionEnd.X, SelectionEnd.Y);
	
	const float Distance = FVector2D::Distance(SelectionStart, SelectionEnd);
	bIsDragging = Distance > DragThreshold;
	if (!bIsDragging) return;
	SelectionWidget->SetVisible(true);
	FVector2D Position(FMath::Min(SelectionStart.X, SelectionEnd.X), FMath::Min(SelectionStart.Y, SelectionEnd.Y));
	FVector2D Size(FMath::Abs(SelectionEnd.X - SelectionStart.X), FMath::Abs(SelectionEnd.Y - SelectionStart.Y));
	
	float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
	Position /= Scale;
	Size /= Scale;
	
	SelectionWidget->SetRectangle(Position, Size);
}

void ARTSPlayerController::EndSelection()
{
	if (bIsDragging)
	{
		HandleBoxSelection();
		SelectionWidget->SetVisible(false);
	}
	else
	{
		HandleSelection();
	}
	bIsDragging = false;
}
