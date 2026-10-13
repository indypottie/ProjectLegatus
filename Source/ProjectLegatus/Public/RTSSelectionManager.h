// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RTSSelectionTypes.h"
#include "Subsystems/WorldSubsystem.h"
#include "RTSSelectionManager.generated.h"

class ARTSUnit;

using FSelectionList = TArray<TObjectPtr<ARTSUnit>>;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRTSSelectionChanged, const FSelectionList&);

UCLASS()
class PROJECTLEGATUS_API URTSSelectionManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	
	void Select(ARTSUnit* Unit, ERTSSelectionMode SelectionMode);
	void Select(const TArray<ARTSUnit*>& Units, ERTSSelectionMode SelectionMode);
	void ClearSelection();
	const FSelectionList& GetSelectedUnits() const;
	
	FOnRTSSelectionChanged& OnSelectionChanged(){return SelectionChangedEvent;}
	
private:
	
	void AddToSelection(ARTSUnit* Unit);
	void RemoveFromSelection(ARTSUnit* Unit);
	
	UPROPERTY()
	TArray<TObjectPtr<ARTSUnit>> SelectedUnits;
	
	FOnRTSSelectionChanged SelectionChangedEvent;
	void ClearSelectionInternal();
};
