// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LocationManager.generated.h"


class AFloor;
class AObstacle;

USTRUCT()
struct FFloorArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AFloor*> Array;
};

// LocationManager instantiate map from json file
// and contains all information about grid and object that stands on it

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API ULocationManager : public USceneComponent
{
	GENERATED_BODY()

public:	
	ULocationManager();

    FORCEINLINE TArray<FFloorArray>& GetFloorArray() { return FloorArray; }

	UPROPERTY()
	TArray<FFloorArray> FloorArray;

	UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	TSubclassOf<AFloor> FloorClass;

	UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	TSubclassOf<AActor> WallClass;

	UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	TSubclassOf<AActor> BombClass;

    UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
    TSubclassOf<AObstacle> ObstacleClass;

	UPROPERTY()
	AActor* GridParent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	float OriginX;

	UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	float OriginY;

	AActor* CreateBomb(int& i, int& j);

    void GenerateMap();

protected:
	virtual void BeginPlay() override;

private:

	enum MapElements {
		Wall = 1,
        Obstacle,
		Floor,
		Player,
	};

	void CreateWall(int& i, int& j);
    void CreateObstacle (int& i, int& j);
	AFloor* CreateFloor(int& i, int& j);

	const int BLOCK_SIZE = 100;
};
