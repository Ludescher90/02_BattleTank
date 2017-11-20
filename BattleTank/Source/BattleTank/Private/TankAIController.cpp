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

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	ControlledTank->Fire();

}



void ATankAIController::MoveTowardsPlayerTank()
{
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

}


