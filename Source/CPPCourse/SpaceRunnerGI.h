// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpaceRunnerGI.generated.h"

/**
 * 
 */
UCLASS()
class CPPCOURSE_API USpaceRunnerGI : public UGameInstance
{
	GENERATED_BODY()
protected:
	USpaceRunnerGI();

public:
	float SpeedMod;
	
};