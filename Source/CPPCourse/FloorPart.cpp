// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorPart.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFloorPart::AFloorPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spawned = nullptr;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	//SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void AFloorPart::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ASpaceRunnerGM>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AFloorPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFloorPart::GetFloorLength()
{
	return FloorLength;
}

void AFloorPart::Spawn(FVector SpawnPos)
{
	if (ToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;

			FRotator rotator;

			float y = GameMode->GetWidth();

			y = FMath::RandRange(-y, y);

			float z = FMath::FRandRange(0, GameMode->GetHeight());

			FVector spawnLocation;

			spawnLocation.Y = y;

			spawnLocation.Z = z;


			FRotator MyRot;

			Spawned = world->SpawnActor<AActor>(ToSpawn, spawnLocation, MyRot, spawnParams);

			FAttachmentTransformRules AttachRules =
				FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

			Spawned->AttachToActor(this, AttachRules);
		}
	}
}

void AFloorPart::Despawn()
{
	if (Spawned)
	{
		Spawned->Destroy();
	}
}

