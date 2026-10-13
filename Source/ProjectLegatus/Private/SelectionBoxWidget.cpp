// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionBoxWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

void USelectionBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USelectionBoxWidget::SetVisible(bool bVisible)
{
	SetVisibility(bVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}

void USelectionBoxWidget::SetRectangle(const FVector2D& Position, const FVector2D& Size)
{
	if (!SelectionBox) return;
	
	UCanvasPanelSlot* WidgetSlot = Cast<UCanvasPanelSlot>(Slot);
	if (!WidgetSlot) return;
	
	WidgetSlot->SetPosition(Position);
	WidgetSlot->SetSize(Size);
}
