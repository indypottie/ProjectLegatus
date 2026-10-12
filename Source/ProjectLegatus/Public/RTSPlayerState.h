// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RTSPlayerState.generated.h"

class URTSEconomyComponent;

UCLASS()
class PROJECTLEGATUS_API ARTSPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ARTSPlayerState();
	
	URTSEconomyComponent* GetEconomyComponent() const;
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Economy", meta = (AllowPrivateAccess = true))
	TObjectPtr<URTSEconomyComponent> EconomyComponent;
};
