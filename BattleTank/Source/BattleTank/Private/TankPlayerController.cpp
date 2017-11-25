// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"




	
	

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);

}


void ATankPlayerController::Tick( float DeltaTime ) 
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();

}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } //To protect if no Pawn possed
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation; //OutParameter
	if (GetSightRayHitLocation(HitLocation)) //Has "side effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}

	

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
		
		//Linetrace along that look direction, and see what we hit (up to max range)
		
		GetLookVectorHitLocation(LookDirection, HitLocation);
		
	}
	



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

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if(GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)

	
	)
	{
		HitLocation = HitResult.Location;
		return true;

	}

	
	return false;

}