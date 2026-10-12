#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RTSResourceTypes.h"

#include "RTSEconomyComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnResourceChanged,
	ERTSResourceType,
	ResourceType,
	int32,
	NewAmount
);

UCLASS(ClassGroup = (RTS), meta = (BlueprintSpawnableComponent))
class PROJECTLEGATUS_API URTSEconomyComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	URTSEconomyComponent();

	int32 GetResourceAmount(ERTSResourceType ResourceType) const;
	bool AddResource(ERTSResourceType ResourceType, int32 Amount);
	bool RemoveResource(ERTSResourceType ResourceType, int32 Amount);
	bool CanAfford(const FRTSResourceCost& Cost) const;
	bool SpendResources(const FRTSResourceCost& Cost);

	UPROPERTY(BlueprintAssignable, Category = "Economy")
	FOnResourceChanged OnResourceChanged;

protected:

	void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Economy")
	TArray<FRTSResourceAmount> StartingResources;

private:

	// helpers
	bool BuildResourceTotals(const FRTSResourceCost& Cost, TMap<ERTSResourceType, int64>& OutTotals) const;
	
	UPROPERTY()
	TMap<ERTSResourceType, int32> Resources;
};