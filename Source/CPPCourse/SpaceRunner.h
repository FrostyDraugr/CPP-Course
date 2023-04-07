// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceRunner.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;

UCLASS()
class CPPCOURSE_API ASpaceRunner : public ACharacter
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		class UCameraComponent* ViewCamera;

public:
	// Sets default values for this character's properties
	ASpaceRunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveLeft(float Value);

	void MoveRight(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* ShipMappingContext;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UCameraComponent* GetViewCameraComponent() const
	{
		return ViewCamera;
	}

	void RestartLevel();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float zPosition;
	FVector tempPos = FVector();

	bool CanMove;
};