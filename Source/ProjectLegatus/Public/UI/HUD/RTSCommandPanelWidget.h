#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTSCommandPanelWidget.generated.h"

class ARTSUnit;
class UTextBlock;
class UWidget;

UCLASS()
class PROJECTLEGATUS_API URTSCommandPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshSelection(const TArray<TObjectPtr<ARTSUnit>>& SelectedUnits);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ObjectName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ObjectHealth;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ObjectAttackPower;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ObjectArmor;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> Border_ObjectBuildMenu;
};
