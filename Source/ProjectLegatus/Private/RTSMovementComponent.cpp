// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSMovementComponent.h"

#include "Engine/HitResult.h"

URTSMovementComponent::URTSMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URTSMovementComponent::MoveTo(const FVector& Destination)
{
	TargetLocation = Destination;
	const FVector DesiredLocation = ProjectDestinationToGround(Destination);
	
	if (HasReachedDestination(UpdatedComponent->GetComponentLocation(), DesiredLocation))
	{
		StopMovementImmediately();
		bMoving = false;
		return;
	}

	bMoving = true;
}

void URTSMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!bMoving) return;
	
	const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
	const FVector DesiredLocation = ProjectDestinationToGround(TargetLocation);
	FVector Direction = DesiredLocation - CurrentLocation;
	
	if (HasReachedDestination(CurrentLocation, DesiredLocation))
	{
		bMoving = false;
		StopMovementImmediately();
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
