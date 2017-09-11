// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Find a PlayerTank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank found: %s"), *(PlayerTank->GetName()));
	}

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *(ControlledTank->GetName()));
	}
}



void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	AimTowardsPlayerTank();


}



void ATankAIController::AimTowardsPlayerTank()
{
	auto PlayerTank = GetPlayerTank();
	auto ControlledTank = GetControlledTank();
	
	if (!PlayerTank) { return; }
	if (!ControlledTank) { return; }

	FVector HitLocation = PlayerTank->GetActorLocation();

	GetControlledTank()->AimAt(HitLocation);



}








ATank* ATankAIController::GetControlledTank() const
{
	return	Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {return nullptr;}
	else
	{return Cast<ATank>(PlayerPawn);}
}