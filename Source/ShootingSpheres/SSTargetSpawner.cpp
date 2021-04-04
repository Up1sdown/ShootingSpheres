// Fill out your copyright notice in the Description page of Project Settings.


#include "SSTargetSpawner.h"
#include "SSTarget.h"
#include "Components/SphereComponent.h"
#include "ShootingSpheresGameMode.h"

// Sets default values
ASSTargetSpawner::ASSTargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootSceneComponent;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
}


// Circle Equations
float GetRange(float PrevRange, float PrevValue)
{
	return FMath::Sqrt(FMath::Square(PrevRange) - FMath::Square(PrevValue));
}


// Creating random vector in range
FVector GetRandLocation(float Radius)
{
	float X, Y;
	float YRange;
	X = FMath::FRandRange(-Radius, Radius);
	YRange = GetRange(Radius, X);
	Y = FMath::FRandRange(-YRange, YRange);
	return FVector(X, Y, 0);
}


// Check overlaps with other targets
bool ASSTargetSpawner::CheckLocation(FVector& Location, float SpawnRadius)
{
	int AttemptCount = 0;
	TArray<AActor*> OverlappingActors;

	// changing location until does not overlap with other targets
	do
	{
		Location = GetRandLocation(SpawnRadius);
		CollisionComp->SetRelativeLocation(Location);
		CollisionComp->GetOverlappingActors(OverlappingActors, TSubclassOf<ASSTarget>());
		AttemptCount++;
	} while (OverlappingActors.Num() != 0 && AttemptCount < MaxAttemptCount);

	return AttemptCount < MaxAttemptCount;
}


int ASSTargetSpawner::SpawnTargets(float SpawnRadius, float RightRadius, float DistanceBetweenTargets, int TargetNumber, int RightTargetNumber, float MinScale, float ScaleStep)
{
	int TotalTargetCount = 0;		// How many targets spawned
	int RightTargetCount = 0;		// How many targets spawned in right radius
	bool bIsEnoughSpace = true;
	float InitScale = 1;

	ScaleStep /= 100;
	MinScale /= 100;

	if (TargetClass != nullptr)
	{
		// enable collision
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		while (TotalTargetCount < TargetNumber && bIsEnoughSpace)
		{
			// if number of right targets is not enough 
			if (TargetNumber - TotalTargetCount <= RightTargetNumber - RightTargetCount)
			{
				// changing spawn radius once
				if (RightRadius < SpawnRadius)
				{
					SpawnRadius = RightRadius;
				}
			}

			FVector Location;
			// applying scale to prespawn transform
			FTransform Transform = FTransform();
			Transform.SetScale3D(FVector(InitScale, InitScale, InitScale));

			if (InitScale > MinScale)
			{
				InitScale -= ScaleStep;
			}

			//prespawn target
			ASSTarget* SpawnedTarget = GetWorld()->SpawnActorDeferred<ASSTarget>(TargetClass, Transform);
			CollisionComp->SetSphereRadius(SpawnedTarget->Mesh->Bounds.SphereRadius + DistanceBetweenTargets);
			bIsEnoughSpace = CheckLocation(Location, SpawnRadius);

			if (bIsEnoughSpace)
			{
				Transform.SetLocation(Location + this->GetActorLocation());
				bool bIsRight = Location.Size() <= RightRadius;
				SpawnedTarget->SetRight(bIsRight);
				SpawnedTarget->FinishSpawning(Transform);

				// Adding spawned target to Targets array in gamemode 
				AShootingSpheresGameMode* GM = Cast<AShootingSpheresGameMode>(GetWorld()->GetAuthGameMode());
				GM->Targets.Add(SpawnedTarget);

				if (bIsRight)
				{
					RightTargetCount++;
				}
				TotalTargetCount++;
			}
		}
		// disable collision
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return TotalTargetCount;
}


void ASSTargetSpawner::SetRootLocation(FVector Location)
{
	RootSceneComponent->SetWorldLocation(Location);
}


// Called when the game starts or when spawned
void ASSTargetSpawner::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void ASSTargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

