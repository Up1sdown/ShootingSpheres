// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSTargetSpawner.generated.h"

class ASSTarget;
class USphereComponent;

UCLASS()
class SHOOTINGSPHERES_API ASSTargetSpawner : public AActor
{
	GENERATED_BODY()

	/** Check overlaps with other targets */
	bool CheckLocation(FVector& Location, float SpawnRadius);
	
public:	
	// Sets default values for this actor's properties
	ASSTargetSpawner();

	// RootSceneComponent to move CollisionComp relative to it
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootSceneComponent;

	// CollisionComp to check available locations of the targets
	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* CollisionComp;

	// Target Class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "TargetToSpawn")
	TSubclassOf<ASSTarget> TargetClass;

	// How many times can change location to spawn target
	UPROPERTY(EditDefaultsOnly, Category = "TargetToSpawn")
	int MaxAttemptCount;

	UFUNCTION(BlueprintCallable)
	void SetRootLocation(FVector Location);

	UFUNCTION(BlueprintCallable)
	int SpawnTargets(float SpawnRadius, float RightRadius, float DistanceBetweenSpheres, int SphereCount, int RightSphereCount, float MinScale, float ScaleStep);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
