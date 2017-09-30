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
	MoveTowardsPlayerTank();


}



void ATankAIController::AimTowardsPlayerTank()
{
	
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank && ControlledTank)
	{

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		ControlledTank->Fire(); 

	}

	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Player or ControlledTank Missing in TankAIController"));

	}

}



void ATankAIController::MoveTowardsPlayerTank()
{
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank && ControlledTank) {
	
		MoveToActor(PlayerTank, AcceptanceRadius);
	
	
	}

	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Player or ControlledTank Missing in TankAIController"));

	}
}


