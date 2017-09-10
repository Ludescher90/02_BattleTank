// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"




	
	

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}

	
}


void ATankPlayerController::Tick( float DeltaTime ) 
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}



ATank* ATankPlayerController::GetControlledTank() const
{
	return	Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation; //OutParameter
	if (GetSightRayHitLocation(HitLocation)) //Has "side effect", is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		//TODO TellControlledTankto aim
	}

	
	
	
		//Tell controlled Tank to aim this point

}


//GetworldLocation if Linetrace through crosshair, true if hits Landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	bool HitSomething = true;
	HitLocation = FVector(1.0);


	return HitSomething;
}
