// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

// Forward declaration.
class UActorComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetProjectileBP(TSubclassOf<AProjectile> ShootingProjectile);

	void AimAt(FVector HitLocation);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoLeft() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 2;

	bool IsBarrelMoving();

	void MoveBarrelTowards(FVector AimDirection);

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 Ammo = 10;
};
