// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceRunnerGM.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


ASpaceRunnerGM::ASpaceRunnerGM()
{
	SpeedMod = 1.f;
	MaxSpeed = 10.f;

	MapWidth = 500.f;
	MapHeight = 400.f;

	PrimaryActorTick.bCanEverTick = false;

	i = 0;
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

APlayerController* ASpaceRunnerGM::GetPlayerController()
{
	APlayerController* NewPlayer = UGameplayStatics::GetPlayerController(GetWorld(), i);

	if (NewPlayer == nullptr)
	{
		NewPlayer = UGameplayStatics::CreatePlayer(GetWorld(), i, true);
	}

	i++;

	return NewPlayer;
}
