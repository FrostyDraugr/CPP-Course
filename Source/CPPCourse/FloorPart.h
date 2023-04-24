// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceRunnerGM.h"
#include "Enemy.h"
#include "FloorPart.generated.h"

UCLASS()
class CPPCOURSE_API AFloorPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> ToSpawn;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorMetrics")
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "FloorMetrics")
	USceneComponent* SceneComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetFloorLength();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorMetrics")
		float FloorLength;

	void Spawn(FVector SpawnPos);

	void Despawn();

private:
	AActor* Spawned;

	ASpaceRunnerGM* GameMode;

};
