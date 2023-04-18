// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceshipHUD.h"
#include "Components/ProgressBar.h"

void USpaceshipHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void USpaceshipHUD::SetPower(float CurrentPower, float MaxPower)
{
	if (PowerBar)
	{
		PowerBar->SetPercent(CurrentPower / MaxPower);
	}
}
