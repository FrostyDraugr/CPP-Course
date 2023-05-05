// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SpaceRunnerGM.h"
#include "SpaceRunner.generated.h"

class UInputMappingContext;
class UInputAction;

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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	//UInputAction* MoveAction;

	void Boost(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputMappingContext* ShipMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* MoveAction2;

	void Move(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* FireAction2;

	void Fire(const FInputActionValue& Value);


	UPROPERTY(VisibleAnywhere)
		class UHealthComp* HealthComponent;

	//HUD
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USpaceshipHUD> PlayerHUDClass;

	UPROPERTY()
		class USpaceshipHUD* PlayerHUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		float MaxPower;
		
		float CPower;

		float MaxHealth;



		class ASpaceRunnerGM* GameMode;


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

	UPROPERTY(BlueprintReadOnly)
	float Score;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void Destroyed();
	
	void UpdateHealth(float CurrentH, float MaxH);

	void UpdatePower(float CurrentP, float MaxP);

	UFUNCTION(BlueprintNativeEvent, Category="Death")
	void SaveHighScore();

	void SaveHighScore_Implementation();

private:
	bool MoveHack;
};
