#include "UI/HUD/RTSDeveloperPanelWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Core/Economy/RTSEconomyComponent.h"
#include "GameFramework/PlayerController.h"
#include "Misc/DefaultValueHelper.h"
#include "RTSPlayerState.h"

void URTSDeveloperPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// bind the ui buttons
	if (Button_AddFood)
	{
		Button_AddFood->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::AddFood);
	}

	if (Button_RemoveFood)
	{
		Button_RemoveFood->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::RemoveFood);
	}

	if (Button_AddWood)
	{
		Button_AddWood->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::AddWood);
	}

	if (Button_RemoveWood)
	{
		Button_RemoveWood->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::RemoveWood);
	}

	if (Button_AddStone)
	{
		Button_AddStone->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::AddStone);
	}

	if (Button_RemoveStone)
	{
		Button_RemoveStone->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::RemoveStone);
	}

	if (Button_AddWealth)
	{
		Button_AddWealth->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::AddWealth);
	}

	if (Button_RemoveWealth)
	{
		Button_RemoveWealth->OnClicked.AddUniqueDynamic(this, &URTSDeveloperPanelWidget::RemoveWealth);
	}
	
	// retrieve the economy belonging to this local player
	APlayerController* OwningPlayer = GetOwningPlayer();
	if (!OwningPlayer)
	{
		UE_LOG(LogTemp, Warning,TEXT("Developer panel has no owning PlayerController."));
		return;
	}
	
	ARTSPlayerState* RTSPlayerState = OwningPlayer->GetPlayerState<ARTSPlayerState>();
	if (!RTSPlayerState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Developer panel has no RTSPlayerState."));
		return;
	}
	
	EconomyComponent = RTSPlayerState->GetEconomyComponent();
	
	if (!EconomyComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Developer panel has no EconomyComponent."));
		return;
	}
	
	if (Text_Status)
	{
		Text_Status->SetText(FText::FromString(TEXT("Developer tools ready.")));
	}
}

bool URTSDeveloperPanelWidget::TryGetAmount(int32& OutAmount) const
{
	OutAmount = 0;
	
	if (!EditableTextBox_Amount) return false;
	
	const FString AmountString = EditableTextBox_Amount->GetText().ToString();
	if (!FDefaultValueHelper::ParseInt(AmountString, OutAmount)) return false;
	
	return OutAmount > 0;
}

void URTSDeveloperPanelWidget::ModifyResource(ERTSResourceType ResourceType, bool bAdd)
{
	if (!EconomyComponent)
	{
		if (Text_Status)
		{
			Text_Status->SetText(FText::FromString(TEXT("Error: economy component unavailable.")));
		}
		return;
	}
	
	int32 Amount = 0;
	if (!TryGetAmount(Amount))
	{
		if (Text_Status)
		{
			Text_Status->SetText(FText::FromString(TEXT("Enter a positive whole number.")));
		}
		return;
	}
	
	const bool bSuccess = bAdd ? EconomyComponent->AddResource(ResourceType, Amount) : EconomyComponent->RemoveResource(ResourceType, Amount);
	
	if (!Text_Status) return;
	
	const TCHAR* ResourceName = TEXT("Unknown");

	switch (ResourceType)
	{
	case ERTSResourceType::Food:
		ResourceName = TEXT("Food");
		break;

	case ERTSResourceType::Wood:
		ResourceName = TEXT("Wood");
		break;

	case ERTSResourceType::Stone:
		ResourceName = TEXT("Stone");
		break;

	case ERTSResourceType::Wealth:
		ResourceName = TEXT("Wealth");
		break;

	default:
		return;
	}
	
	if (!bSuccess)
	{
		Text_Status->SetText(FText::FromString(FString::Printf(TEXT("Failed to %s %d %s. Check balance or amount."), bAdd? TEXT("add") : TEXT("remove"), Amount, ResourceName)));
		return;
	}
	
	const int32 NewBalance = EconomyComponent->GetResourceAmount(ResourceType);
	Text_Status->SetText(FText::FromString(FString::Printf(TEXT("%s: %d. New balance: %d."), bAdd ? TEXT("Added") : TEXT("Removed"), Amount, NewBalance)));
}

void URTSDeveloperPanelWidget::AddFood()
{
	ModifyResource(ERTSResourceType::Food, true);
}

void URTSDeveloperPanelWidget::RemoveFood()
{
	ModifyResource(ERTSResourceType::Food, false);
}

void URTSDeveloperPanelWidget::AddWood()
{
	ModifyResource(ERTSResourceType::Wood, true);
}

void URTSDeveloperPanelWidget::RemoveWood()
{
	ModifyResource(ERTSResourceType::Wood, false);
}

void URTSDeveloperPanelWidget::AddStone()
{
	ModifyResource(ERTSResourceType::Stone, true);
}

void URTSDeveloperPanelWidget::RemoveStone()
{
	ModifyResource(ERTSResourceType::Stone, false);
}

void URTSDeveloperPanelWidget::AddWealth()
{
	ModifyResource(ERTSResourceType::Wealth, true);
}

void URTSDeveloperPanelWidget::RemoveWealth()
{
	ModifyResource(ERTSResourceType::Wealth, false);
}
