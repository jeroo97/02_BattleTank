// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
class UStaticMesh;

UCLASS(meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevationDegrees = 0;
};
