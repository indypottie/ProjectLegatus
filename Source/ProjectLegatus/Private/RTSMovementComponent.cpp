// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSMovementComponent.h"

#include "Engine/HitResult.h"
#include "Core/Navigation/RTSNavigationSubsystem.h"
#include "Engine/World.h"

URTSMovementComponent::URTSMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URTSMovementComponent::MoveTo(const FVector& Destination)
{
	if (!UpdatedComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot move because UpdatedComponent is null."), *GetName());
		return;
	}
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	URTSNavigationSubsystem* NavigationSubsystem = World->GetSubsystem<URTSNavigationSubsystem>();
	if (!NavigationSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("No RTSNavigationSubsystem is available for %s"), *GetName());
		return;
	}
	
	TArray<FVector> NewPath;
	const FVector StartLocation = UpdatedComponent->GetComponentLocation();
	
	if (!NavigationSubsystem->FindPath(StartLocation, Destination, NewPath))
	{
		PathPoints.Reset();
		CurrentPathPointIndex = INDEX_NONE;
		bMoving = false;
		StopMovementImmediately();
		UE_LOG(LogTemp, Warning, TEXT("No usable navigation path found for %s."), *GetName());
		return;
	}
	
	TargetLocation = Destination;
	PathPoints = MoveTemp(NewPath);
	
	// the first point represents our starting location 
	CurrentPathPointIndex = 1;
	bMoving	= true;
}

void URTSMovementComponent::SetMovementSettings(const FRTSMovementSettings& NewSettings)
{
	MovementSettings = NewSettings;
}

void URTSMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!bMoving || !UpdatedComponent) return;
	
	if (!PathPoints.IsValidIndex(CurrentPathPointIndex))
	{
		bMoving = false;
		CurrentPathPointIndex = INDEX_NONE;
		StopMovementImmediately();
		return;
	}
	
	const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
	
	// follow the route horizontally for the current flat-map setup.
	FVector Waypoint = PathPoints[CurrentPathPointIndex];
	Waypoint.Z = CurrentLocation.Z;
	
	// advance through the waypoints that are already within reach.
	while (PathPoints.IsValidIndex(CurrentPathPointIndex) && HasReachedDestination(CurrentLocation, Waypoint))
	{
		++CurrentPathPointIndex;
		if (!PathPoints.IsValidIndex(CurrentPathPointIndex))
		{
			bMoving = false;
			CurrentPathPointIndex = INDEX_NONE;
			StopMovementImmediately();
			return;
		}
		
		Waypoint = PathPoints[CurrentPathPointIndex];
		Waypoint.Z = CurrentLocation.Z;
	}
	
	FVector Direction = Waypoint - CurrentLocation;
	Direction.Z = 0.f;
	
	if (Direction.IsNearlyZero())
	{
		return;
	}
	
	Direction.Normalize();
	Velocity = Direction * MovementSettings.MoveSpeed;
	FHitResult Hit;
	
	SafeMoveUpdatedComponent(Velocity * DeltaTime, UpdatedComponent->GetComponentQuat(), true, Hit);
	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(Velocity * DeltaTime, 1.f - Hit.Time, Hit.Normal, Hit);
	}
}

FVector URTSMovementComponent::ProjectDestinationToGround(const FVector& DesiredLocation) const
{
	FVector ProjectedLocation = DesiredLocation;
	ProjectedLocation.Z = UpdatedComponent->GetComponentLocation().Z;
	return ProjectedLocation;
}

bool URTSMovementComponent::HasReachedDestination(const FVector& CurrentLocation, const FVector& DesiredLocation) const
{
	return FVector::DistSquared(CurrentLocation, DesiredLocation) <= FMath::Square(MovementSettings.DistanceThreshold);
}

float URTSMovementComponent::GetMaxSpeed() const
{
	return MovementSettings.MoveSpeed;
}
