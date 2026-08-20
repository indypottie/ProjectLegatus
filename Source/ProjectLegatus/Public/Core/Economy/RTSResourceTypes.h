#pragma once

#include "CoreMinimal.h"
#include "RTSResourceTypes.generated.h"

UENUM(BlueprintType)
enum class ERTSResourceType : uint8
{
	Food,
	Wood,
	Stone,
	Wealth
};


USTRUCT(BlueprintType)
struct FRTSResourceAmount
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	ERTSResourceType ResourceType = ERTSResourceType::Food;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (ClampMin = "0"))
	int32 Amount = 0;
	
};

USTRUCT(BlueprintType)
struct FRTSResourceCost
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TArray<FRTSResourceAmount> Resources;
};
