// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

#include "RTSHUDWidget.h"
#include "Blueprint/UserWidget.h"

void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!RootWidgetClass) return;

	RootWidget = CreateWidget<URTSHUDWidget>(GetOwningPlayerController(), RootWidgetClass);

	if (RootWidget)
	{
		RootWidget->AddToViewport();
	}
}
