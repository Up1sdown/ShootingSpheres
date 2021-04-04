// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSTarget.generated.h"

UCLASS()
class SHOOTINGSPHERES_API ASSTarget : public AActor
{
	GENERATED_BODY()
	

	// Target in right radius from spawner
	UPROPERTY(EditAnywhere, meta = (ExposepOnSpawn = true), Category = "Target")
	bool bIsRight;
	
public:	
	// Sets default values for this actor's properties
	ASSTarget();

	/** Target mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	/** Explosion particle */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* Emitter;

	/** Called when get hit */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void SetRight(bool bRight);

	UFUNCTION(BlueprintCallable)
	bool GetRight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
