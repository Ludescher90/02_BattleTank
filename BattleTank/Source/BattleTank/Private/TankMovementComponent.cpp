// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"




void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;

	RightTrack = RightTrackToSet;

	//TODO Prevent that no input double...

}




void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT(" %s: throttle  axis value: %f "), *Name, Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}




void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT(" %s: throttle  axis value: %f "), *Name, Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we are replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();


	IntendMoveForward(FVector::DotProduct(AIForwardIntention, TankForward));


	//UE_LOG(LogTemp, Warning, TEXT("%s Wants to move: %s "), *Name, *MoveVelocity.GetSafeNormal().ToString());


}