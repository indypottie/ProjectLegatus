// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

#include "RTSHUDWidget.h"
#include "RTSPlayerController.h"
#include "Blueprint/UserWidget.h"

USelectionBoxWidget* ARTSHUD::GetSelectionBoxWidget() const
{
	if (!RootWidget) return nullptr;
	return RootWidget->GetSelectionBoxWidget();
}

void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("ARTSHUD:BehinPlay called"));

	if (!RootWidgetClass) return;

	RootWidget = CreateWidget<URTSHUDWidget>(GetOwningPlayerController(), RootWidgetClass);

	if (RootWidget)
	{
		RootWidget->AddToViewport();
	}
	
	if (ARTSPlayerController* PC = Cast<ARTSPlayerController>(GetOwningPlayerController()))
	{
		PC->SetSelectionWidget(GetSelectionBoxWidget());
	}
}
