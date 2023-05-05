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

#include "SpaceshipHUD.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Enemy.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
ASpaceRunner::ASpaceRunner()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));

	GetCharacterMovement()->MaxFlySpeed = 300.0f;
	GetCharacterMovement()->DefaultLandMovementMode = MOVE_Flying;
	GetCharacterMovement()->BrakingDecelerationFlying = 5.0f;

	HealthComponent = CreateDefaultSubobject<UHealthComp>(TEXT("Health Component"));

	//HUD
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	MaxPower = 100.f;

	Score = 0;

	MoveHack = true;

	Player2 = nullptr;
	SkipInput = false;
}

// Called when the game starts or when spawned
void ASpaceRunner::BeginPlay()
{
	Super::BeginPlay();

	
	//UE_LOG(LogTemp, Warning, TEXT("Testing"));

	//APlayerController* PlayerController = Cast<APlayerController>(GetController());

	GameMode = Cast<ASpaceRunnerGM>(UGameplayStatics::GetGameMode(GetWorld()));

	APlayerController* PlayerController = GameMode->GetPlayerController();


	if (PlayerController)
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ShipMappingContext, 0);
		}

			if (GetWorld()->GetFirstPlayerController() != PlayerController)
			{
				ASpaceRunner* Player1 = Cast<ASpaceRunner>(GetWorld()->GetFirstPlayerController()->GetPawn());
				
				if (Player1)
				{
					Player1->Player2 = this;
					SkipInput = true;
				}
			}



	}

	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<USpaceshipHUD>(PlayerController, PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();
		PlayerHUD->SetHealth(HealthComponent->Health, HealthComponent->DefaultHealth);
	}

	UpdateHealth(HealthComponent->Health, HealthComponent->DefaultHealth);

	CPower = MaxPower;
}

void ASpaceRunner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		//Offloading destruction of widget to Garbace Collector
		PlayerHUD = nullptr;
	}
}



// Called every frame
void ASpaceRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CPower += DeltaTime;
	CPower = FMath::Clamp(CPower, 0.f, 100.f);

	UpdatePower(CPower, MaxPower);

	if (GameMode)
	{
	Score += DeltaTime * 10 * (GameMode->GetSpeedMod());
	PlayerHUD->SetScore(Score);
	}

	if (MoveHack)
	{
		AddMovementInput(GetActorRightVector() * 0.1f);
	}
	else
	{
		AddMovementInput(GetActorRightVector() * -0.1f);
	}

	MoveHack = !MoveHack;
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

	if (Controller && !(MoveAxisValue.IsZero()))
	{
		AddMovementInput(GetActorUpVector() * MoveAxisValue.Y);
		AddMovementInput(GetActorRightVector() * MoveAxisValue.X);
	}
}

void ASpaceRunner::Move2(const FInputActionValue& Value)
{
	if (Player2)
	{
		Player2->Move(Value);
	}
}

void ASpaceRunner::Fire(const FInputActionValue& Value)
{
	if (CPower < 10.f)
	{
		return;
	}

	CPower -= 10.f;
	
	FHitResult Hit;
	
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * 3000);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility,
		Params, FCollisionResponseParams()))
	{
		AEnemy* Target = Cast<AEnemy>(Hit.GetActor());

		if (Target)
		{
			UE_LOG(LogTemp, Warning, TEXT("Valid Target!"));

			FPointDamageEvent DamageEvent(3.f, Hit, this->GetActorForwardVector(), nullptr);
			Target->TakeDamage(3.f, DamageEvent, GetController(), this);
		}

		UE_LOG(LogTemp, Warning, TEXT("Hit!"));
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f);

}

void ASpaceRunner::Fire2(const FInputActionValue& Value)
{
	if (Player2)
	{
		Player2->Fire(Value);
	}
}

void ASpaceRunner::RestartLevel()
{

}

// Called to bind functionality to input
void ASpaceRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
			
		if (SkipInput)
			return;

			UE_LOG(LogTemp, Warning, TEXT("Setup Player 1 Input"));

			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
				&ASpaceRunner::Move);

			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this,
				&ASpaceRunner::Fire);

			UE_LOG(LogTemp, Warning, TEXT("Setup Player 2 Input"));

			EnhancedInputComponent->BindAction(MoveAction2, ETriggerEvent::Triggered, 
				this, &ASpaceRunner::Move2);

			EnhancedInputComponent->BindAction(FireAction2, ETriggerEvent::Started, 
				this, &ASpaceRunner::Fire2);

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
}

void ASpaceRunner::UpdateHealth(float CurrentH, float MaxH)
{
	PlayerHUD->SetHealth(CurrentH, MaxH);
}

void ASpaceRunner::UpdatePower(float CurrentP, float MaxP)
{
	PlayerHUD->SetPower(CurrentP, MaxP);
}

void ASpaceRunner::SaveHighScore_Implementation()
{

}