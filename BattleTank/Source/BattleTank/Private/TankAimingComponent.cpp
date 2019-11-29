// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo > 0)
	{
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		{
			FiringState = EFiringStatus::Reloading;
		}
		else if (IsBarrelMoving())
		{
			FiringState = EFiringStatus::Aiming;
		}
		else
		{
			FiringState = EFiringStatus::Locked;
		}
	}
	else
	{
		FiringState = EFiringStatus::NoAmmo;
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// So that no one can fire in the begin play.
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet)
		return;
	
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::SetProjectileBP(TSubclassOf<AProjectile> ShootingProjectile)
{
	ProjectileBlueprint = ShootingProjectile;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
		return;

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
		return;

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimsAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimsAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBlueprint))
		return;

	if (FiringState != EFiringStatus::Reloading && FiringState != EFiringStatus::NoAmmo)
	{
		// Spawn projectile at the socket of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Ammo--;
	}
}


