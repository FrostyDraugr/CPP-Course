// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceRunnerGM.h"

ASpaceRunnerGM::ASpaceRunnerGM()
{
	SpeedMod = 1.f;
	MaxSpeed = 10.f;

	MapWidth = 500.f;
	MapHeight = 400.f;

	PrimaryActorTick.bCanEverTick = false;
}

void ASpaceRunnerGM::IncreaseSpeedMod(float increase)
{
	SpeedMod += increase;
	SpeedMod = FMath::Clamp(SpeedMod, 1.f, MaxSpeed);
}

float ASpaceRunnerGM::GetSpeedMod()
{
	return SpeedMod;
}

float ASpaceRunnerGM::GetWidth()
{
	return MapHeight;
}

float ASpaceRunnerGM::GetHeight()
{
	return MapWidth;
}
