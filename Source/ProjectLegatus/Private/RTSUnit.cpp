// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSUnit.h"

#include "RTSMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/RTSCollisionChannels.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ARTSUnit::ARTSUnit()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);
	
	RTSMovementComponent = CreateDefaultSubobject<URTSMovementComponent>(TEXT("MovementComponent"));
	
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(RTSCollisionChannels::UnitSelection, ECR_Block);
	
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::Disabled;
}

// Called when the game starts or when spawned
void ARTSUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTSUnit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	RTSMovementComponent->SetUpdatedComponent(CapsuleComponent);
}

// Called every frame
void ARTSUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARTSUnit::SetSelected(bool Selected)
{
	if (bIsSelected == Selected) return;
	
	bIsSelected = Selected;
	if (bIsSelected)
	{
		MeshComponent->SetOverlayMaterial(SelectionOverlayMaterial);
	}
	else
	{
		MeshComponent->SetOverlayMaterial(nullptr);
	}
}

bool ARTSUnit::IsUnitSelected() const
{
	return bIsSelected;
}

UPawnMovementComponent* ARTSUnit::GetMovementComponent() const
{
	return RTSMovementComponent;
}

void ARTSUnit::MoveTo(const FVector& Destination)
{
	RTSMovementComponent->MoveTo(Destination);
}
