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
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *HitLocation.ToString());
		//TODO TellControlledTankto aim
	}

	
	
	
		//Tell controlled Tank to aim this point

}


//GetworldLocation if Linetrace through crosshair, true if hits Landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	//"Deproject" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		
			UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());

		
	}
	//Linetrace along that look direction, and see what we hit (up to max range)



	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	
return (DeprojectScreenPositionToWorld(
		ScreenLocation.X, ScreenLocation.Y, 
		CameraWorldLocation, LookDirection
	
	));
	
}