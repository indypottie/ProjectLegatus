// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSFormationMarker.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ARTSFormationMarker::ARTSFormationMarker()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	MarkerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MarkerMesh"));
	MarkerMesh->SetupAttachment(Root);
}

void ARTSFormationMarker::SetMarkerLocation(const FVector& Location)
{
	SetActorLocation(Location);
}