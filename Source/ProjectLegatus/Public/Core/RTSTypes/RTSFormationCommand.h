#pragma once

#include "CoreMinimal.h"
#include "RTSFormationCommand.generated.h"

USTRUCT(BlueprintType)
struct FRTSFormationCommand
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector TargetLocation = FVector::ZeroVector;
	
	UPROPERTY()
	FVector ForwardDirection = FVector::ForwardVector;
};
