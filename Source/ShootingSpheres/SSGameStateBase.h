// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SSGameStateBase.generated.h"


UCLASS()
class SHOOTINGSPHERES_API ASSGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	ASSGameStateBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CurrentRightTargetDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int WaveCount;
};
