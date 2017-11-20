// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"// Must be the last include

/**
 * Responsible for helping the PLayer aim.
 */

//Forward Declaration

class UTankAimingComponent;


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	//Start the tan moving the barrel so that a shot would it where 
	//the crosshair intersects the world

	void AimTowardsCrosshair();

	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	
	bool GetLookDirection(FVector2D ScreenLcoation, FVector& LookDirection) const;

	//Return an OUT Parameter, true if it Hit anything
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	
};
