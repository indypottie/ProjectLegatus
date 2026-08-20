// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Formation/FormationData.h"
#include "Subsystems/WorldSubsystem.h"
#include "RTSFormationManager.generated.h"

struct FRTSFormationCommand;
class ARTSUnit;
struct FFormationSlot;
/**
 * 
 */
UCLASS()
class PROJECTLEGATUS_API URTSFormationManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	TArray<FFormationSlot> BuildFormation(const TArray<ARTSUnit*>& Units, const FRTSFormationCommand& Command);
	
private:
	TArray<FFormationSlot> BuildSquareFormation(const TArray<ARTSUnit*>& Units, const FRTSFormationCommand& Command);
	
	
	// formation data 
	FFormationData FormationData;
};
