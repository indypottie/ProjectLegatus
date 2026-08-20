// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSFormationManager.h"

#include "RTSUnit.h"
#include "Core/Formation/FormationData.h"
#include "Core/Formation/FormationTypes.h"
#include "Core/RTSTypes/RTSFormationCommand.h"

TArray<FFormationSlot> URTSFormationManager::BuildFormation(const TArray<ARTSUnit*>& Units, const FRTSFormationCommand& Command)
{
	switch (FormationData.FormationType)
	{
	case EFormationType::Line:
		
		
		break;
	case EFormationType::Column:
		
		
		break;
	case EFormationType::Square:
		return BuildSquareFormation(Units, Command);
	case EFormationType::Wedge:
		
		
		break;
	}
	
	return {};
}

TArray<FFormationSlot> URTSFormationManager::BuildSquareFormation(const TArray<ARTSUnit*>& Units, const FRTSFormationCommand& Command)
{
	TArray<FFormationSlot> Slots;
	
	// determine nr of columns and rows
	const int32 UnitCount = Units.Num();
	
	const int32 Columns = FMath::CeilToInt(FMath::Sqrt(static_cast<float>(UnitCount)));
	const int32 Rows = FMath::CeilToInt(static_cast<float>(UnitCount) / Columns);
	
	// calculate axes 
	const FVector Forward = Command.ForwardDirection.GetSafeNormal();
	const FVector Right = FVector::CrossProduct(FVector::UpVector, Forward);
	
	// centre formation
	const float Width = (Columns - 1) * FormationData.UnitSpacing;
	const float Height = (Rows - 1) * FormationData.RankSpacing;
	
	for (int32 Index = 0; Index < UnitCount; ++Index)
	{
		const int32 Row = Index / Columns;
		const int32 Column = Index % Columns;
		
		const float ForwardOffset = (Height * 0.5f) - (Row * FormationData.RankSpacing);
		const float RightOffset = (Column * FormationData.UnitSpacing) - (Width * 0.5f);
		
		// transform to world space 
		FFormationSlot Slot;
		
		Slot.AssignedUnit = Units[Index];
		Slot.WorldLocation = Command.TargetLocation + Forward * ForwardOffset + Right * RightOffset;
		Slot.Rotation = Forward.Rotation();
		
		Slots.Add(Slot);
	}
	
	return Slots;
}
