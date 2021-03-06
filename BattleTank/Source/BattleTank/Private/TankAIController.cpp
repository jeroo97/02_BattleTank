// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.h" // So we can implement OnDeath.


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
			return;

		PossessedTank->TankDie.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
		// TODO Subscribe our local method to the tank's death event.
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn())
		return;

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank || ControlledTank))
		return;

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank))
		return;
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire at the player.
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}