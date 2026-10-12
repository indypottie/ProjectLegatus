#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RTSNavigationSubsystem.generated.h"

UCLASS()
class PROJECTLEGATUS_API URTSNavigationSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	/**
	 * Finds a path between two world locations using Unreal navigation.
	 *
	 * @param StartLocation The unit's current world location.
	 * @param Destination The requested destination.
	 * @param OutPath Receives the path points, including start and end.
	 * @return True if a usable path was found.
	 */
	
	bool FindPath(const FVector& StartLocation, const FVector& Destination, TArray<FVector>& OutPath) const;
};