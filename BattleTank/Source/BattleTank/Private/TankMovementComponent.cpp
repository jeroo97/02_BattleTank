// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


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

