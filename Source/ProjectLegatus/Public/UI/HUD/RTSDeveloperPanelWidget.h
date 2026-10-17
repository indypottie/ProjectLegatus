#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Economy/RTSResourceTypes.h"
#include "RTSDeveloperPanelWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class URTSEconomyComponent;
class UButton;

UCLASS()
class PROJECTLEGATUS_API URTSDeveloperPanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_Amount;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Status;
	
	// buttons
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_AddFood;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_RemoveFood;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_AddWood;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_RemoveWood;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_AddStone;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_RemoveStone;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_AddWealth;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_RemoveWealth;
	
private:
	UPROPERTY()
	TObjectPtr<URTSEconomyComponent> EconomyComponent;
	
	bool TryGetAmount(int32& OutAmount) const;
	void ModifyResource(ERTSResourceType ResourceType, bool bAdd);
	
	UFUNCTION()
	void AddFood();

	UFUNCTION()
	void RemoveFood();

	UFUNCTION()
	void AddWood();

	UFUNCTION()
	void RemoveWood();

	UFUNCTION()
	void AddStone();

	UFUNCTION()
	void RemoveStone();

	UFUNCTION()
	void AddWealth();

	UFUNCTION()
	void RemoveWealth();
};
