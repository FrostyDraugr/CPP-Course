// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "HealthComp.h"
//#include "Components/SphereComponent.h"
//#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "SpaceRunner.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComp>(TEXT("Health Component"));

/*	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Asteroid Object"));
	SphereComponent->InitSphereRadius(50.f);
	SphereComponent->bAlwaysCreatePhysicsState = true*/;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//StaticMesh->SetSimulatePhysics(true);
	StaticMesh->bAlwaysCreatePhysicsState = true;
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->SetCollisionProfileName("BlockAllDynamic");
	StaticMesh->OnComponentHit.AddDynamic(this, &AEnemy::OnCompHit);

	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit Component!"));

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherActor != NULL))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid Actor Check!"));

		ASpaceRunner* Player = Cast<ASpaceRunner>(OtherActor);
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Valid Player Check!"));

			FPointDamageEvent DamageEvent(3.f, Hit, this->GetActorForwardVector(), nullptr);
			Player->TakeDamage(1.f, DamageEvent, nullptr, this);
			this->Destroy();
		}
	}
}

