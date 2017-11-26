// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
//Forward Declaration
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 5000;


private:
	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;


	void AimTowardsPlayerTank();

	void MoveTowardsPlayerTank();
	
	//How close can the AITank move to the PlayerTank
	

};
