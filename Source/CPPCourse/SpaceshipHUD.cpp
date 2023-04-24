// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceshipHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

void USpaceshipHUD::SetScore(int32 score)
{
	if (TextBlock)
	{
		FString string = FString::FromInt(score);
		FText Text = FText::FromString(string);
		TextBlock->SetText(Text);
	}
}
