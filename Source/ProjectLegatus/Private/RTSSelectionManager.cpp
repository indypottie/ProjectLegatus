// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSSelectionManager.h"

#include "RTSUnit.h"

void URTSSelectionManager::Select(ARTSUnit* Unit, ERTSSelectionMode SelectionMode)
{
	if (!Unit) return;
	
	TArray<ARTSUnit*> Units;
	Units.Add(Unit);
	Select(Units, SelectionMode);
}

void URTSSelectionManager::Select(const TArray<ARTSUnit*>& Units, ERTSSelectionMode SelectionMode)
{
	if (Units.IsEmpty()) return;

	if (SelectionMode == ERTSSelectionMode::Replace)
	{
		ClearSelection();
	}

	if (SelectionMode == ERTSSelectionMode::Replace ||
		SelectionMode == ERTSSelectionMode::Add)
	{
		for (ARTSUnit* Unit : Units)
		{
			AddToSelection(Unit);
		}

		return;
	}

	// Toggle
	for (ARTSUnit* Unit : Units)
	{
		if (!Unit) continue;

		if (SelectedUnits.Contains(Unit))
		{
			RemoveFromSelection(Unit);
		}
		else
		{
			AddToSelection(Unit);
		}
	}
}

void URTSSelectionManager::AddToSelection(ARTSUnit* Unit)
{
	if (!Unit) return;
	if (SelectedUnits.Contains(Unit)) return;
	
	SelectedUnits.Add(Unit);
	Unit->SetSelected(true);
}

void URTSSelectionManager::RemoveFromSelection(ARTSUnit* Unit)
{
	if (!Unit) return;
	
	if (SelectedUnits.Remove(Unit) > 0)
	{
		Unit->SetSelected(false);
	}
}

const FSelectionList& URTSSelectionManager::GetSelectedUnits() const
{
	return SelectedUnits;
}

void URTSSelectionManager::ClearSelection()
{
	for (ARTSUnit* Unit : SelectedUnits)
	{
		Unit->SetSelected(false);
	}
	
	SelectedUnits.Empty();
}
