// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCommandManager.h"

#include "RTSFormationManager.h"
#include "RTSUnit.h"
#include "Core/Formation/FormationData.h"
#include "Engine/World.h"

void URTSCommandManager::IssueMoveCommand(const FSelectionList& Units, const FRTSFormationCommand& Command)
{
	URTSFormationManager* FormationManager = GetWorld()->GetSubsystem<URTSFormationManager>();
	if (!FormationManager) return;
	
	const TArray<FFormationSlot> Formation = FormationManager->BuildFormation(Units, Command);
	
	for (const FFormationSlot& Slot : Formation)
	{
		if (!Slot.AssignedUnit) continue;
		Slot.AssignedUnit->MoveTo(Slot.WorldLocation);
	}
}
