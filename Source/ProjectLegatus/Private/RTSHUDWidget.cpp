// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUDWidget.h"

#include "UI/HUD/RTSCommandPanelWidget.h"

USelectionBoxWidget* URTSHUDWidget::GetSelectionBoxWidget() const
{
	return SelectionBoxWidget;
}

void URTSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	BoundSelectionManager = World->GetSubsystem<URTSSelectionManager>();
	if (!BoundSelectionManager) return;
	
	SelectionChangeHandle = BoundSelectionManager->OnSelectionChanged().AddUObject(this, &URTSHUDWidget::HandleSelectionChanged);
	HandleSelectionChanged(BoundSelectionManager->GetSelectedUnits());
}

void URTSHUDWidget::NativeDestruct()
{
	if (BoundSelectionManager && SelectionChangeHandle.IsValid())
	{
		BoundSelectionManager->OnSelectionChanged().Remove(SelectionChangeHandle);
	}
	
	SelectionChangeHandle.Reset();
	BoundSelectionManager = nullptr;
	
	Super::NativeDestruct();
}

void URTSHUDWidget::HandleSelectionChanged(const FSelectionList& SelectedUnits)
{
	if (CommandPanelWidget)
	{
		CommandPanelWidget->RefreshSelection(SelectedUnits);
	}
}
