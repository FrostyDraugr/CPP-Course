// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceRunner.h"

// Sets default values
ASpaceRunner::ASpaceRunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpaceRunner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceRunner::MoveLeft(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Moving Left", Value));
}

void ASpaceRunner::MoveRight(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Moving Right", Value));
}

void ASpaceRunner::RestartLevel()
{

}

// Called to bind functionality to input
void ASpaceRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpaceRunner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

