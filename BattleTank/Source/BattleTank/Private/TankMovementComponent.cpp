// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Math/Vector.h"


void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!RightTrackToSet || !LeftTrackToSet)  
		return;  // TODO check why "IsValid" isn't working.
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
	// TODO prevent double-speed due to dual control use.
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::ActivateTurbo(bool bActivate)
{
	if (bActivate)
	{
		Speed = Speed * 20;
		UE_LOG(LogTemp, Warning, TEXT("Turbo activated, speed = %f"), Speed);
	}
	else
	{
		Speed = NormalSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Turbo deactivated, speed = %f"), Speed);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality.
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);

	auto TurnThrow = FVector::CrossProduct(AIForwardIntention, TankForward);
	IntendTurnRight(TurnThrow.Z);
}

