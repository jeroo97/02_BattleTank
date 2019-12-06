// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

	// How colse can the AI tank get to the player.
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	float AcceptanceRadius = 8000;

private:

	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

	virtual void Tick(float DeltaTime) override;
};

