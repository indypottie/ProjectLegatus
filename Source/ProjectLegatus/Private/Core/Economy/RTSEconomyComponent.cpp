

#include "Core/Economy/RTSEconomyComponent.h"

URTSEconomyComponent::URTSEconomyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URTSEconomyComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Resources.Empty();
	
	for (const auto& StartingResource : StartingResources)
	{
		if (StartingResource.Amount <= 0)
		{
			continue;
		}
		
		int32& CurrentAmount = Resources.FindOrAdd(StartingResource.ResourceType);
		
		if (StartingResource.Amount > MAX_int32 - CurrentAmount)
		{
			UE_LOG(LogTemp, Error, TEXT("Starting resource amount exceeds int32 capacity."));
			continue;
		}
		
		CurrentAmount += StartingResource.Amount;
	}
	
	for (const auto& Resource : Resources)
	{
		OnResourceChanged.Broadcast(Resource.Key, Resource.Value);
	}
}

bool URTSEconomyComponent::BuildResourceTotals(const FRTSResourceCost& Cost, TMap<ERTSResourceType, int64>& OutTotals) const
{
	OutTotals.Reset();
	
	for (const FRTSResourceAmount& ResourceCost : Cost.Resources)
	{
		// Negative and zero entries are invalid.
		if (ResourceCost.Amount <= 0) return false;
		
		int64& TotalAmount = OutTotals.FindOrAdd(ResourceCost.ResourceType);
		TotalAmount += static_cast<int64>(ResourceCost.Amount);
		
		// Balances are stored as int32, so a cost cannot legitimately require more than that.
		if (TotalAmount > MAX_int32) return false;
	}
	return true;
}

int32 URTSEconomyComponent::GetResourceAmount(ERTSResourceType ResourceType) const
{
	if (const int32* Amount = Resources.Find(ResourceType))
	{
		return *Amount;
	}
	
	return 0;
}

bool URTSEconomyComponent::AddResource(ERTSResourceType ResourceType, int32 Amount)
{
	if (Amount <= 0) return false;
	
	const int32 CurrentAmount = GetResourceAmount(ResourceType);
	
	// reject additions that would overflow the stored balance 
	if (Amount > MAX_int32 - CurrentAmount) return false;
	
	const int32 NewAmount = CurrentAmount + Amount;
	Resources.Add(ResourceType, NewAmount);
	OnResourceChanged.Broadcast(ResourceType, NewAmount);
	return true;
}

bool URTSEconomyComponent::RemoveResource(ERTSResourceType ResourceType, int32 Amount)
{
	if (Amount <= 0) return false;
	
	int32* CurrentAmount = Resources.Find(ResourceType);
	
	if (!CurrentAmount) return false;
	if (*CurrentAmount < Amount) return false;
	
	*CurrentAmount -= Amount;
	OnResourceChanged.Broadcast(ResourceType, *CurrentAmount);
	return true;
}

bool URTSEconomyComponent::CanAfford(const FRTSResourceCost& Cost) const
{
	TMap<ERTSResourceType, int64> RequiredTotals;
	if (!BuildResourceTotals(Cost, RequiredTotals)) return false;
	
	for (const auto& RequiredResource : RequiredTotals)
	{
		const int32 AvailableAmount = GetResourceAmount(RequiredResource.Key);
		if (static_cast<int64>(AvailableAmount) < RequiredResource.Value) return false;
	}
	return true;
}

bool URTSEconomyComponent::SpendResources(const FRTSResourceCost& Cost)
{
	TMap<ERTSResourceType, int64> RequiredTotals;
	
	if (!BuildResourceTotals(Cost, RequiredTotals)) return false;
	//Phase 1: Validate every resource before changing anything
	for (const auto& RequiredResource : RequiredTotals)
	{
		const int32 AvailableAmount = GetResourceAmount(RequiredResource.Key);
		if (static_cast<int64>(AvailableAmount) < RequiredResource.Value) return false;
	}
	
	// Phase 2: apply all deductions, no operation below this point should fail
	TMap<ERTSResourceType, int32> UpdatedBalances;
	for (const auto& RequiredResource : RequiredTotals)
	{
		const int32 CurrentAmount = GetResourceAmount(RequiredResource.Key);
		const int32 AmountToSpend = static_cast<int32>(RequiredResource.Value);
		const int32 NewAmount = CurrentAmount - AmountToSpend;
		
		Resources.Add(RequiredResource.Key, NewAmount);
		UpdatedBalances.Add(RequiredResource.Key, NewAmount);
	}
	
	// Phase 3: notify all listeners after all balances are updated.
	for (const auto& UpdatedBalance : UpdatedBalances)
	{
		OnResourceChanged.Broadcast(UpdatedBalance.Key, UpdatedBalance.Value);
	}
	return true;
}



