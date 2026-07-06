// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSUnit.generated.h"

class UCapsuleComponent;

UCLASS(abstract)
class PROJECTLEGATUS_API ARTSUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void SetSelected(bool Selected);
	virtual bool IsUnitSelected() const;
	
	// Public Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(visibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(editdefaultsOnly)
	TObjectPtr<UMaterialInterface> SelectionOverlayMaterial;
	
private:
	
	// private variables
	bool bIsSelected = false;
};
