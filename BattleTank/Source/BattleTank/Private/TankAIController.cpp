// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}



void ATankAIController::Tick( float DeltaTime )
{

	Super::Tick( DeltaTime );
	
	AimTowardsPlayerTank();


}



void ATankAIController::AimTowardsPlayerTank()
{
	
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank && ControlledTank)
	{

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		ControlledTank->Fire(); // TODO Firing Limit Rate

	}

	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Player or ControlledTank Missing in TankAIController"));

	}

}






