// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for firing state
UENUM()
enum class EFiringState : uint8 {Reloading, Aiming, Locked};

//Forward Declarations:
class UTankBarrel; 
class UTankTurret;
class AProjectile;

//Holds Barrels properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;


private:


	void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection);


	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	
	
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	//Stores FPlatformTimeSeconds when fired
	double LastFireTime = 0;

};
