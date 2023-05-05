// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceRunnerGM.generated.h"

/**
 * 
 */
UCLASS()
class CPPCOURSE_API ASpaceRunnerGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASpaceRunnerGM();

	void IncreaseSpeedMod(float increase);

	float GetSpeedMod();

	float GetWidth();

	float GetHeight();

	APlayerController* GetPlayerController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float MaxSpeed;

	float SpeedMod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boundaries")
		float MapHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boundaries")
		float MapWidth;

private:
	int32 i;
};
