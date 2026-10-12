#include "Core/Navigation/RTSNavigationSubsystem.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

bool URTSNavigationSubsystem::FindPath(const FVector& StartLocation, const FVector& Destination, TArray<FVector>& OutPath) const
{
	OutPath.Reset();
	
	UWorld* World = GetWorld();
	if (!World) return false;
	
	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (!NavigationSystem) return false;
	
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(World, StartLocation, Destination);
	if (!NavigationPath || !NavigationPath->IsValid()) return false;
	
	OutPath = NavigationPath->PathPoints;
	return OutPath.Num() >= 2;
}
