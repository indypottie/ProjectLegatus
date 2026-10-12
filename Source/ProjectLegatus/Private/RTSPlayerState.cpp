// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerState.h"

#include "Core/Economy/RTSEconomyComponent.h"

ARTSPlayerState::ARTSPlayerState()
{
	EconomyComponent = CreateDefaultSubobject<URTSEconomyComponent>(TEXT("EconomyComponent"));
}

URTSEconomyComponent* ARTSPlayerState::GetEconomyComponent() const
{
	return EconomyComponent;
}
