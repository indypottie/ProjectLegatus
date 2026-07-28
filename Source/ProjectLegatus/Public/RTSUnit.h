// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSUnit.generated.h"

class URTSMovementComponent;
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
	
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void SetSelected(bool Selected);
	virtual bool IsUnitSelected() const;
	
	// Public overrides
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	
	// Public Functions
	void MoveTo(const FVector& Destination);
	
	// Public Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(visibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(editdefaultsOnly)
	TObjectPtr<UMaterialInterface> SelectionOverlayMaterial;
	
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category="Movement")\
	TObjectPtr<URTSMovementComponent> RTSMovementComponent;
	
private:
	
	// private variables
	bool bIsSelected = false;
};
