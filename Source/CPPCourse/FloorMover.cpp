// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorMover.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFloorMover::AFloorMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorOffset = 0.f;
}

// Called when the game starts or when spawned
void AFloorMover::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ASpaceRunnerGM>(UGameplayStatics::GetGameMode(GetWorld()));

	for (int32 i = 0; i < NumberOfParts; i++)
	{
		Spawn(i);
	}
}

// Called every frame
void AFloorMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode)
	{
		GameMode->IncreaseSpeedMod(DeltaTime * 0.1f);
	
	for(AActor* Actor : Floor)
	{
		FVector Position = Actor->GetActorLocation();

		float XMod = GameMode->GetSpeedMod() * -10.f;

		FVector UPosition = Position;
		
		UPosition.X += XMod;

		ETeleportType TPType = ETeleportType::None;

		Actor->SetActorLocation(UPosition, false, NULL, TPType);
		
		if (Actor->GetActorLocation().X <= -400.f)
		{
			AFloorPart* FloorPartS = Cast<AFloorPart>(Actor);

			FloorPartS->Despawn();

			if (FMath::FRandRange(0, 100) < 10 && PrevActor)
			{
				Cast<AFloorPart>(PrevActor)->Despawn();
			}

			FVector NewPos = Actor->GetActorLocation();

			NewPos.X += (NumberOfParts * FloorOffset);

			FloorPartS->SetActorLocation(NewPos, false, NULL, TPType);

			FloorPartS->Spawn(FloorPartS->GetActorLocation());
		}

		PrevActor = Actor;
	}
	}
}

void AFloorMover::Spawn(int32 index)
{
	AActor* FloorSpawn = nullptr;

	if (FloorPart)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;

			FRotator rotator;

			float x = index * FloorOffset;

			FVector spawnLocation = GetActorLocation();

			spawnLocation.X += x;

			FRotator MyRot;

			FloorSpawn = world->SpawnActor<AActor>(FloorPart, spawnLocation, MyRot, spawnParams);;
		}

		if (index == 0)
		{
			FloorOffset = Cast<AFloorPart>(FloorSpawn)->GetFloorLength();
		}

		Floor.Add(FloorSpawn);
	}
}

