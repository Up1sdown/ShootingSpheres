// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingSpheresGameMode.h"
#include "ShootingSpheresHUD.h"
#include "ShootingSpheresCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SSTargetSpawner.h"
#include "SSTarget.h"
#include "SSGameStateBase.h"

AShootingSpheresGameMode::AShootingSpheresGameMode()
	: Super()
{
	// fkingshit, den' v pomoiku
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShootingSpheresHUD::StaticClass();
}


void AShootingSpheresGameMode::TargetDestroyed(ASSTarget* Destroyed)
{
	if (Destroyed)
	{
		// remove destroyed target from array
		Targets.RemoveSingle(Destroyed);

		if (Destroyed->GetRight())
		{			
			GS->CurrentRightTargetDestroyed++;
			if (GS->CurrentRightTargetDestroyed == TargetToProceedWave)
			{
				WaveCleared();
			}
		}
	}
}


void AShootingSpheresGameMode::IncreaseParameters()
{
	SpawnRadius += SpawnRadius * SpawnRadiusInc / 100;
	TargetNumber += TargetNumber * TargetNumberInc / 100;
}


// destroying left targets and clean up array
void AShootingSpheresGameMode::DestroyLeftTargets()
{
	for (ASSTarget* Target : Targets)
	{
		Target->Destroy();
	}
	Targets.Empty();
}


void AShootingSpheresGameMode::SpawnNewWave()
{
	GS->WaveCount++;
	GS->CurrentRightTargetDestroyed = 0;
	if (ASSTargetSpawner* TargetSpawner = Cast<ASSTargetSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), TargetSpawnerClass)))
	{
		TargetSpawner->RootSceneComponent->SetWorldLocation(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
		TargetSpawner->SpawnTargets(SpawnRadius, RightRadius, DistanceBetweenTargets, TargetNumber, TargetToProceedWave, MinScale, ScaleStep);
	}
}

void AShootingSpheresGameMode::WaveCleared()
{
	DestroyLeftTargets();
	IncreaseParameters();
	SpawnNewWave();
}

// Called when the game starts or when spawned
void AShootingSpheresGameMode::BeginPlay()
{
	Super::BeginPlay();
	GS = GetGameState<ASSGameStateBase>();
	SpawnNewWave();
} 