// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCommandManager.h"

#include "RTSUnit.h"

void URTSCommandManager::IssueMoveCommand(const FSelectionList& Units, const FVector& Destination)
{
	for (ARTSUnit* Unit : Units)
	{
		if (!Unit) continue;
	
		UE_LOG(LogTemp, Warning,
			TEXT("Move command issued to %s (%s)"),
			*Unit->GetName(),
			*Destination.ToString()
		);
	
		Unit->MoveTo(Destination);
	}
}
