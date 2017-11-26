// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initial Reload Time
	LastFireTime = FPlatformTime::Seconds();


	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );


	SetFiringState();

}



void UTankAimingComponent::SetFiringState()
{
	if (FiringState != EFiringState::NoAmmo)
	{
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		{


			FiringState = EFiringState::Reloading;



		}

		else if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}

		else
		{
			FiringState = EFiringState::Locked;
		}
	}

	else
	{
		FiringState = EFiringState::NoAmmo;
	}
}

void UTankAimingComponent::SetAmmoState()
{
	if (AmmoState > 1)
	{
		AmmoState--;
	}
	else
	{
		AmmoState--;
		FiringState = EFiringState::NoAmmo;

	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();

	return !BarrelForwardVector.Equals(AimDirection,0.01);
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}



EFiringState UTankAimingComponent::GetFiringState() const
{

	return FiringState;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace 
	)
		);

	if(bHaveAimSolution)

	{
		auto Time = GetWorld()->GetTimeSeconds();
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		
		MoveBarrelTowards(AimDirection);
	
	}

	//Do nothing if no solution found
}

void UTankAimingComponent::Fire()
{

	if (!ensure(Barrel)) { return; }
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{

		//Spawn a Projectile at the socket location on the barrel

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		SetAmmoState();
		


	}


	else
	{
		//TODO Text in UI that tells you why you cant fire
	}
}



void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{	
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//Work-out difference between current rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
    DeltaRotator =	DeltaRotator.GetNormalized();

	//Always yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch); //DeltaRotator clamped in TankBarrel

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else //Avoid taking the long way
	{
		Turret->RotateTurret(-DeltaRotator.Yaw);
	}
}


