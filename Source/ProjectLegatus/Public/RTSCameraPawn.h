// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USceneComponent;

USTRUCT(BlueprintType)
struct FRTSCameraSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed = 3000.f;
	
	UPROPERTY(EditAnywhere, Category="Zoom")
	float ZoomSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category="Zoom")
	float MinZoom = 1200.f;

	UPROPERTY(EditAnywhere, Category="Zoom")
	float MaxZoom = 8000.f;

	UPROPERTY(EditAnywhere, Category="Rotation")
	float RotationSpeed = 90.f;
};

UCLASS()
class PROJECTLEGATUS_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSCameraPawn();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCameraComponent> Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveCamera(const FVector2D& Input);
	void ZoomCamera(float Value);
	void RotateCamera(float Value);
	
	// variables
	UPROPERTY(editAnywhere, Category="RTS Camera Settings")
	FRTSCameraSettings Settings;
	
private:
	// private functions
	void HandleMovement(float DeltaTime);
	void HandleRotation(float DeltaTime);
	void HandleZoom(float DeltaTime);
	
	// private variables
	FVector MovementInput;
	float RotationInput;
	float TargetZoom;
};
