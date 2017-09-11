// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{
		// Move The Barrel the right amount this frame
		//Given a max elevation speed, and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate() called at %f Degrees per Second"), DegreesPerSecond);
}

