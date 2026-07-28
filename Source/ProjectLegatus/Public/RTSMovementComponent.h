// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "RTSMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FRTSMovementSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Speed")
	float MoveSpeed = 300.f;
	
	UPROPERTY(EditAnywhere, Category="DistanceThreshold")
	float DistanceThreshold = 5.f;
};

UCLASS()
class PROJECTLEGATUS_API URTSMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	URTSMovementComponent();
	
	virtual float GetMaxSpeed() const override;
	
	void MoveTo(const FVector& Destination);
	
protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	// private helper functions
	FVector ProjectDestinationToGround(const FVector& DesiredLocation) const;
	bool HasReachedDestination(const FVector& CurrentLocation, const FVector& DesiredLocation) const;
	
	// movement settings
	UPROPERTY(EditAnywhere)
	FRTSMovementSettings MovementSettings;
	
	// variables
	FVector TargetLocation;
	
	bool bMoving = false;
};
