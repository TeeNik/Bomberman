// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameMode.generated.h"

class ULocationManager;
class UBombManager;

UCLASS(minimalapi)
class ABombermanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABombermanGameMode();

	virtual void BeginPlay() override;

	FORCEINLINE class ULocationManager* GetLocationManager() { return LocationManager; }
	FORCEINLINE class UBombManager* GetBombManager() { return BombManager; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Managers")
	ULocationManager* LocationManager;

	UPROPERTY(EditDefaultsOnly, Category = "Managers")
	UBombManager* BombManager;
};



