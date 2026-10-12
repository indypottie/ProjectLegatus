

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
		CurrentAmount += StartingResource.Amount;
	}
	
	for (const auto& Resource : Resources)
	{
		OnResourceChanged.Broadcast(Resource.Key, Resource.Value);
	}
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
	
	int32& CurrentAmount = Resources.FindOrAdd(ResourceType);
	CurrentAmount += Amount;
	
	OnResourceChanged.Broadcast(ResourceType, CurrentAmount);
	
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
	for (const auto& ResourceCost : Cost.Resources)
	{
		if (ResourceCost.Amount <= 0) return false;
		if (GetResourceAmount(ResourceCost.ResourceType) < ResourceCost.Amount) return false;
	}
	return true;
}

bool URTSEconomyComponent::SpendResources(const FRTSResourceCost& Cost)
{
	if (!CanAfford(Cost)) return false;
	
	for (const auto& ResourceCost : Cost.Resources)
	{
		if (ResourceCost.Amount <= 0) continue;
		RemoveResource(ResourceCost.ResourceType, ResourceCost.Amount);
	}
	return true;
}



