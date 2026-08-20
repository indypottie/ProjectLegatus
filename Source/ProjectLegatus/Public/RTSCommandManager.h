// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSSelectionManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "RTSCommandManager.generated.h"

struct FRTSFormationCommand;
class ARTSUnit;
/**
 * 
 */
UCLASS()
class PROJECTLEGATUS_API URTSCommandManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	
	void IssueMoveCommand(const FSelectionList& Units, const FRTSFormationCommand& Command);
	
};
