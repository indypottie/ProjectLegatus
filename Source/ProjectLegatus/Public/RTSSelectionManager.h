// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RTSSelectionTypes.h"
#include "Subsystems/WorldSubsystem.h"
#include "RTSSelectionManager.generated.h"

class ARTSUnit;

using FSelectionList = TArray<TObjectPtr<ARTSUnit>>;

UCLASS()
class PROJECTLEGATUS_API URTSSelectionManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	
	void Select(ARTSUnit* Unit, ERTSSelectionMode SelectionMode);
	void Select(const TArray<ARTSUnit*>& Units, ERTSSelectionMode SelectionMode);
	void ClearSelection();
	const FSelectionList& GetSelectedUnits() const;
	
private:
	
	void AddToSelection(ARTSUnit* Unit);
	void RemoveFromSelection(ARTSUnit* Unit);
	
	UPROPERTY()
	TArray<TObjectPtr<ARTSUnit>> SelectedUnits;
};
