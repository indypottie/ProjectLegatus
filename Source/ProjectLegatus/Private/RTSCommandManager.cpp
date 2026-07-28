// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCommandManager.h"

#include "RTSUnit.h"

void URTSCommandManager::IssueMoveCommand(ARTSUnit* Unit, const FVector& Destination)
{
	if (!Unit) return;
	
	UE_LOG(LogTemp, Warning,
		TEXT("Move command issued to %s (%s)"),
		*Unit->GetName(),
		*Destination.ToString()
	);
	
	Unit->MoveTo(Destination);
}
