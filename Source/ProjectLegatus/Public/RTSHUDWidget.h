// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTSHUDWidget.generated.h"

class USelectionBoxWidget;
/**
 * 
 */
UCLASS()
class PROJECTLEGATUS_API URTSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USelectionBoxWidget* GetSelectionBoxWidget() const;
	
protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USelectionBoxWidget> SelectionBoxWidget;
};
