#include "UI/HUD/RTSResourceBarWidget.h"

#include "Components/TextBlock.h"
#include "Core/Economy/RTSEconomyComponent.h"
#include "RTSPlayerState.h"
#include "GameFramework/PlayerController.h"

void URTSResourceBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	APlayerController* OwningPlayer = GetOwningPlayer();
	if (!OwningPlayer) return;
	
	ARTSPlayerState* RTSPlayerState = OwningPlayer->GetPlayerState<ARTSPlayerState>();
	if (!RTSPlayerState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Resource bar could not find ARTSPlayerState."));
		return;
	}
	
	BoundEconomyComponent = RTSPlayerState->GetEconomyComponent();
	if (!BoundEconomyComponent) return;
	
	BoundEconomyComponent->OnResourceChanged.AddDynamic(this, &URTSResourceBarWidget::HandleResourceChanged);
	
	// read the current balances immediately.
	RefreshAllResources();
}

void URTSResourceBarWidget::NativeDestruct()
{
	if (BoundEconomyComponent)
	{
		BoundEconomyComponent->OnResourceChanged.RemoveDynamic(this, &URTSResourceBarWidget::HandleResourceChanged);
	}
	
	BoundEconomyComponent = nullptr;
	
	Super::NativeDestruct();
}

void URTSResourceBarWidget::HandleResourceChanged(ERTSResourceType ResourceType, int32 NewAmount)
{
	UpdateResourceText(ResourceType, NewAmount);
}

void URTSResourceBarWidget::RefreshAllResources()
{
	if (!BoundEconomyComponent) return;

	UpdateResourceText(ERTSResourceType::Food,	 BoundEconomyComponent->GetResourceAmount(ERTSResourceType::Food));
	UpdateResourceText(ERTSResourceType::Wood,	 BoundEconomyComponent->GetResourceAmount(ERTSResourceType::Wood));
	UpdateResourceText(ERTSResourceType::Stone,	 BoundEconomyComponent->GetResourceAmount(ERTSResourceType::Stone));
	UpdateResourceText(ERTSResourceType::Wealth, BoundEconomyComponent->GetResourceAmount(ERTSResourceType::Wealth));
}

void URTSResourceBarWidget::UpdateResourceText(ERTSResourceType ResourceType, int32 Amount)
{
	UTextBlock* TargetText = nullptr;
	FText ResourceName;

	switch (ResourceType)
	{
	case ERTSResourceType::Food:
		TargetText = Text_Food;
		ResourceName = NSLOCTEXT("RTSHUD", "Food", "Food");
		break;
		
	case ERTSResourceType::Wood:
		TargetText = Text_Wood;
		ResourceName = NSLOCTEXT("RTSHUD", "Wood", "Wood");
		break;
		
	case ERTSResourceType::Stone:
		TargetText = Text_Stone;
		ResourceName = NSLOCTEXT("RTSHUD", "Stone", "Stone");
		break;
		
	case ERTSResourceType::Wealth:
		TargetText = Text_Wealth;
		ResourceName = NSLOCTEXT("RTSHUD", "Wealth", "Wealth");
		break;
		
	default:
		return;
	}
	
	if (TargetText)
	{
		TargetText->SetText(FText::Format(NSLOCTEXT("RTSHUD", "ResourceAmountFormat", "{0}: {1}"), ResourceName, FText::AsNumber(Amount)));
	}
}
