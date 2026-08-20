// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RTSResourceTypes.h"
#include "RTSResourceDefinition.generated.h"

class UTexture2D;

UCLASS(BlueprintType)
class PROJECTLEGATUS_API URTSResourceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
	ERTSResourceType ResourceType = ERTSResourceType::Food;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
	FText DisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
	TObjectPtr<UTexture2D> Icon;
	
};
