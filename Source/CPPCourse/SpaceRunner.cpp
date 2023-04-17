// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceRunner.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "HealthComp.h"

#include "Engine/World.h"

// Sets default values
ASpaceRunner::ASpaceRunner()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));

	GetCharacterMovement()->MaxFlySpeed = 300.0f;
	GetCharacterMovement()->DefaultLandMovementMode = MOVE_Flying;
	GetCharacterMovement()->BrakingDecelerationFlying = 5.0f;

	tempPos = GetActorLocation();
	zPosition = tempPos.Z + 300.0f;

	HealthComponent = CreateDefaultSubobject<UHealthComp>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ASpaceRunner::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Testing"));

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ShipMappingContext, 0);
		}
	}
}

// Called every frame
void ASpaceRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceRunner::Boost(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_JUMP triggered"));
	}
}

void ASpaceRunner::Move(const FInputActionValue& Value)
{
	const FVector2D MoveAxisValue = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("MovementTriggered: %s"), *MoveAxisValue.ToString());

	if (Controller && !(MoveAxisValue.IsZero()))
	{
		AddMovementInput(GetActorUpVector() * MoveAxisValue.Y);
		AddMovementInput(GetActorRightVector() * MoveAxisValue.X);
	}
}

void ASpaceRunner::Fire(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	
	FHitResult Hit;
	
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * 3000);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility,
		Params, FCollisionResponseParams()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit!"));
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f);

}

void ASpaceRunner::RestartLevel()
{

}

// Called to bind functionality to input
void ASpaceRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UE_LOG(LogTemp, Warning, TEXT("Setup Player Input"));

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Started, this,
			&ASpaceRunner::Boost);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
			&ASpaceRunner::Move);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this,
			&ASpaceRunner::Fire);
	}
}

void ASpaceRunner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ASpaceRunner::Destroyed()
{
	Super::Destroyed();

	UE_LOG(LogTemp, Warning, TEXT("I was Destroyed!!"));

}

