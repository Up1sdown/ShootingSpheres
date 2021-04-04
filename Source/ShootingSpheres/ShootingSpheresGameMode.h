// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingSpheresGameMode.generated.h"

UCLASS(minimalapi)
class AShootingSpheresGameMode : public AGameModeBase
{
	GENERATED_BODY()

	class ASSGameStateBase* GS;

public:
	AShootingSpheresGameMode();

	void TargetDestroyed(class ASSTarget* Destroyed);

	void WaveCleared();	

	void IncreaseParameters();

	void DestroyLeftTargets();

	void SpawnNewWave();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASSTargetSpawner> TargetSpawnerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RightRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceBetweenTargets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int TargetNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int TargetToProceedWave;

	// increase in %
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnRadiusInc;

	// increase in %
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetNumberInc;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ScaleStep;
		
	UPROPERTY()
	TArray<class ASSTarget*> Targets;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};