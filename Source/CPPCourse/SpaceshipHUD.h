// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpaceshipHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CPPCOURSE_API USpaceshipHUD : public UUserWidget
{
	GENERATED_BODY()
	
	public:
		//Update HUD with current Health
		void SetHealth(float CurrentHealth, float MaxHealth);

		//Update HUD with current power
		void SetPower(float CurrentPower, float MaxPower);

		void SetScore(int32 score);

		UPROPERTY(EditAnywhere, meta = (BindWidget))
			class UProgressBar* HealthBar;
		
		UPROPERTY(EditAnywhere, meta = (BindWidget))
			class UProgressBar* PowerBar;

		UPROPERTY(EditAnywhere, meta = (BindWidget))
			class UTextBlock* TextBlock;
};
