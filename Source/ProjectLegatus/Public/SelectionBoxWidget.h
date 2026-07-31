// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectionBoxWidget.generated.h"

class UButton;

UCLASS()
class PROJECTLEGATUS_API USelectionBoxWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	void SetVisible(bool bVisible);
	void SetRectangle(const FVector2D& Position, const FVector2D& Size);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SelectionBox;
	
};
