// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceRunnerGM.h"
#include "FloorPart.h"
#include "FloorMover.generated.h"

UCLASS()
class CPPCOURSE_API AFloorMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
		int32 NumberOfParts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
		TSubclassOf<AFloorPart> FloorPart;

	float FloorOffset;

	TArray<AActor*> Floor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void Spawn(int32 index);

	ASpaceRunnerGM* GameMode;
};
