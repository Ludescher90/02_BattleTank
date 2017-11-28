// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"




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

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!PossessedTank) { return; }

	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	// Subscribe our local Method to the TanksDeathEvent


}

void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();

}
void ATankAIController::AimTowardsPlayerTank()
{
	
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	

	if (!ensure(PlayerTank) && !ensure (ControlledTank)) { return; }

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if(AimingComponent->GetFiringState() == EFiringState::Locked)

	{
	
		AimingComponent->Fire();

	}

}



void ATankAIController::MoveTowardsPlayerTank()
{
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

}


