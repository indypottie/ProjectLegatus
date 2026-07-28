// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLEGATUS_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class URTSHUDWidget> RootWidgetClass;

private:

	UPROPERTY()
	TObjectPtr<URTSHUDWidget> RootWidget;
};
