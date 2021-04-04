// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootingSpheresHUD.generated.h"

UCLASS()
class AShootingSpheresHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShootingSpheresHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

