// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
