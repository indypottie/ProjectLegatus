#pragma once

#include "CoreMinimal.h"
#include "RTSMovementSettings.generated.h"

USTRUCT(BlueprintType)
struct FRTSMovementSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (ClampMin = "0.0")) 
	float MoveSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (ClampMin = "0.0"))
	float DistanceThreshold = 5.f;
};
