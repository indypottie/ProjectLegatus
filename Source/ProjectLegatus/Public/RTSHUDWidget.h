// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include  "RTSSelectionManager.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTSHUDWidget.generated.h"

class URTSCommandPanelWidget;
class USelectionBoxWidget;
class ARTSUnit;



/**
 * 
 */
UCLASS()
class PROJECTLEGATUS_API URTSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USelectionBoxWidget* GetSelectionBoxWidget() const;
	
protected: 
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URTSCommandPanelWidget> CommandPanelWidget;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USelectionBoxWidget> SelectionBoxWidget;
	
private:
	UPROPERTY()
	TObjectPtr<URTSSelectionManager> BoundSelectionManager;
	
	FDelegateHandle SelectionChangeHandle;
	
	void HandleSelectionChanged(const FSelectionList& SelectedUnits);
};
