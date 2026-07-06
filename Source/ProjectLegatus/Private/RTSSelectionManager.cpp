// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSSelectionManager.h"

#include "RTSUnit.h"

void URTSSelectionManager::SelectUnit(ARTSUnit* Unit)
{
	if (SelectedUnit == Unit) return;
	
	ClearSelection();
	SelectedUnit = Unit;
	
	if (SelectedUnit)
	{
		SelectedUnit->SetSelected(true);
	}
}

void URTSSelectionManager::ClearSelection()
{
	if (SelectedUnit)
	{
		SelectedUnit->SetSelected(false);
	}
	
	SelectedUnit = nullptr;
}

ARTSUnit* URTSSelectionManager::GetSelectedUnit() const
{
	return SelectedUnit;
}
