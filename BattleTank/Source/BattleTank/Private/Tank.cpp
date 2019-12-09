// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "..\Public\Tank.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TankTurret.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//UE_LOG(LogTemp, Warning, TEXT("Tank C++ -> Constructor."));
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

void ATank::SetTurret(UTankTurret * TurretToSet)
{
	TankTurret = TurretToSet;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("%s, is taking damage"), *GetName());
	int32 DamegePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamegePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		TankDie.Broadcast();
		if (!bIsTankDeath)
		{
			TankDieBehaviour();
			bIsTankDeath = true;
		}
	}

	return DamageToApply;
}

void ATank::TankDieBehaviour()
{
	if (!ensure(TankTurret))
		return;

	TankTurret->SetAbsolute(true, true, false);
	TankTurret->SetWorldLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100));
	TankTurret->SetSimulatePhysics(true);
	auto ForceDeathExplosion = TankTurret->GetForwardVector() * 5000;
	auto TurretLocation = TankTurret->GetComponentLocation();
	TankTurret->AddForceAtLocation(ForceDeathExplosion, TurretLocation);
}
