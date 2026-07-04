// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

/**
 * 
 */
UCLASS()
class PROJECTLEGATUS_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARTSPlayerController();
	
	virtual void SetupInputComponent() override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	
	UFUNCTION()
	void MoveCamera(const FInputActionValue& Value);
};
