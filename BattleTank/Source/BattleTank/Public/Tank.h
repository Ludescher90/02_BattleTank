// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations:
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	//TODO remove once firing is moved to AimingComponent
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000; // Sensible starting Value of 1000 m/s

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	//Stores FPLatformTimeSeconds when fired
	double LastFireTime = 0;

	//Local barrel reference for spawning Projectile
	UTankBarrel* Barrel = nullptr;

	
};
