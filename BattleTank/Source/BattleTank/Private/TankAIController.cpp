// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"
#include "GameFramework/Actor.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!IsValid(PlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find PlayerTank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
	}

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing any tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is possessed by the AI"), *(ControlledTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!IsValid(PlayerPawn)) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}
