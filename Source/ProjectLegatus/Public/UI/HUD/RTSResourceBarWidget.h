#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Economy/RTSResourceTypes.h"
#include "RTSResourceBarWidget.generated.h"

class UTextBlock;
class URTSEconomyComponent;

UCLASS()
class PROJECTLEGATUS_API URTSResourceBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Food;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Wood;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Stone;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Wealth;
	
private:
	UPROPERTY()
	TObjectPtr<URTSEconomyComponent> BoundEconomyComponent;
	
	UFUNCTION()
	void HandleResourceChanged(ERTSResourceType ResourceType, int32 NewAmount);
	
	void RefreshAllResources();
	void UpdateResourceText(ERTSResourceType ResourceType, int32 Amount);
};