// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core/Movement/RTSMovementSettings.h"
#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "RTSMovementComponent.generated.h"


UCLASS()
class PROJECTLEGATUS_API URTSMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	URTSMovementComponent();
	
	virtual float GetMaxSpeed() const override;
	
	void MoveTo(const FVector& Destination);
	void SetMovementSettings(const FRTSMovementSettings& NewSettings);
	
protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	// private helper functions
	FVector ProjectDestinationToGround(const FVector& DesiredLocation) const;
	bool HasReachedDestination(const FVector& CurrentLocation, const FVector& DesiredLocation) const;
	
	// movement settings
	UPROPERTY(Transient)
	FRTSMovementSettings MovementSettings;
	
	// variables
	FVector TargetLocation;
	
	bool bMoving = false;
};
