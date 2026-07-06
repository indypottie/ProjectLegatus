// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "RTSPlayerController.generated.h"

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
	
	// properties
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_MoveCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_ZoomCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_RotateCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Select;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Command;
	
protected:
	virtual void BeginPlay() override;
	
private:
	
	UFUNCTION()
	void MoveCamera(const FInputActionValue& Value);
	
	UFUNCTION()
	void ZoomCamera(const FInputActionValue& Value);
	
	UFUNCTION()
	void RotateCamera(const FInputActionValue& Value);
	
	UFUNCTION()
	void HandleSelection();
	
	UFUNCTION()
	void HandleCommand();
};
