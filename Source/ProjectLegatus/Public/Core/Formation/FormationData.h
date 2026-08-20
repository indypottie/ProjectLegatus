#pragma once

#include "CoreMinimal.h"
#include "FormationTypes.h"
#include "FormationData.generated.h"

class ARTSUnit;

USTRUCT(BlueprintType)
struct FFormationSlot
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector WorldLocation = FVector::ZeroVector;
	
	UPROPERTY()
	FRotator Rotation = FRotator::ZeroRotator;
	
	UPROPERTY()
	TObjectPtr<ARTSUnit> AssignedUnit = nullptr;
};

USTRUCT(BlueprintType)
struct FFormationData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	EFormationType FormationType = EFormationType::Square;
	
	UPROPERTY(EditAnywhere)
	float UnitSpacing = 150.f;
	
	UPROPERTY(EditAnywhere)
	float RankSpacing = 150.f;
};