#include "UI/HUD/RTSCommandPanelWidget.h"

#include "RTSUnit.h"
#include "Core/Units/RTSUnitDefinition.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"

void URTSCommandPanelWidget::RefreshSelection(const TArray<TObjectPtr<ARTSUnit>>& SelectedUnits)
{
	const int32 SelectedCount = SelectedUnits.Num();
	
	if (SelectedCount == 0)
	{
		Text_ObjectName->SetText(FText::GetEmpty());
		Text_ObjectHealth->SetText(FText::GetEmpty());
		Text_ObjectAttackPower->SetText(FText::GetEmpty());
		Text_ObjectArmor->SetText(FText::GetEmpty());
		Border_ObjectBuildMenu->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	
	if (SelectedCount > 1)
	{
		Text_ObjectName->SetText(FText::Format(NSLOCTEXT("RTSHUD", "UnitsSelected", "{0} Units Selected"), FText::AsNumber(SelectedCount)));
		Text_ObjectHealth->SetText(FText::GetEmpty());
		Text_ObjectAttackPower->SetText(FText::GetEmpty());
		Text_ObjectArmor->SetText(FText::GetEmpty());
		Border_ObjectBuildMenu->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	
	ARTSUnit* Unit = SelectedUnits[0];
	if (!IsValid(Unit)) return;
	
	FText DisplayName = FText::FromString(TEXT("Unit"));
	if (Unit->UnitDefinition && !Unit->UnitDefinition->DisplayName.IsEmpty())
	{
		DisplayName = Unit->UnitDefinition->DisplayName;
	}
	
	Text_ObjectName->SetText(DisplayName);
	
	// health and combat stats dont exist yet TODO: implement once stats exist
	Text_ObjectHealth->SetText(FText::FromString(TEXT("Health")));
	Text_ObjectAttackPower->SetText(FText::FromString(TEXT("AttackPower")));
	Text_ObjectArmor->SetText(FText::FromString(TEXT("Armor")));
	
	const bool bCanBuild = Unit->UnitDefinition && Unit->UnitDefinition->bCanBuild;
	Border_ObjectBuildMenu->SetVisibility(bCanBuild ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
