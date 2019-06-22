// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LocationManager.generated.h"


class AFloor;

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

	//UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	//TSubclassOf<AFloor> FloorClass;

	UPROPERTY()
	AActor* GridParent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	float OriginX;

	UPROPERTY(EditDefaultsOnly, Category = "LocationManager")
	float OriginY;

protected:
	virtual void BeginPlay() override;

private:

	enum MapElements {
		Wall = 1,
		Destructible,
		Floor,
		Player,
	};

	void GenerateMap();
	void CreateWall(int& i, int& j);
	void CreateDestructable(int& i, int& j);
	void CreateFloor(int& i, int& j);

	const int BLOCK_SIZE = 100;
};
