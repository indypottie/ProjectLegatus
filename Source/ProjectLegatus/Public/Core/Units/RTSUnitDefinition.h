#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Core/Movement/RTSMovementSettings.h"
#include "RTSUnitDefinition.generated.h"

UCLASS(BlueprintType)
class PROJECTLEGATUS_API URTSUnitDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Unit")
	FText DisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FRTSMovementSettings MovementSettings;
};
