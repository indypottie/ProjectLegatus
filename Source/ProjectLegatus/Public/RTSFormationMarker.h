// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSFormationMarker.generated.h"

UCLASS()
class PROJECTLEGATUS_API ARTSFormationMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTSFormationMarker();
	
	void SetMarkerLocation(const FVector& Location);

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MarkerMesh;
	
};
