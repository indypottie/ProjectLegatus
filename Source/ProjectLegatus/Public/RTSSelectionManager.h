// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RTSSelectionManager.generated.h"

class ARTSUnit;
/**
 * 
 */
UCLASS()
class PROJECTLEGATUS_API URTSSelectionManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	
	void SelectUnit(ARTSUnit* Unit);
	void ClearSelection();
	ARTSUnit* GetSelectedUnit() const;
	
private:
	
	UPROPERTY()
	TObjectPtr<ARTSUnit> SelectedUnit = nullptr;
};
