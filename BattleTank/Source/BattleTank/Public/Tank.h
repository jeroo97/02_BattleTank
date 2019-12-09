// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

class APawn;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	FTankDelegate TankDie;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurret(UTankTurret* TurretToSet);

	// Called by the engine when actor damage is dealt.
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	// Returns current health as a percentage of starting health, between 0 and 1,
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 StartingHealth = 200;

	UTankTurret* TankTurret = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialized on BeginPlay().

	bool bIsTankDeath = false;

	void TankDieBehaviour();
 
};
