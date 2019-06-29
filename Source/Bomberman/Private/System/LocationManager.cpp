#include "LocationManager.h"
#include "InputCoreTypes.h"
#include "Engine/World.h"
#include "JsonUtilities.h"
#include "Obstacle.h"
#include "Floor.h"

ULocationManager::ULocationManager()
{
}

void ULocationManager::BeginPlay()
{
	Super::BeginPlay();
}

void ULocationManager::GenerateMap()
{
	const FString JsonFilePath = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + "ThirdPersonCPP/Data/map.json";
	FString JsonString;

	GLog->Log("Path: " + JsonFilePath);

	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

	GLog->Log("Json String:");
	GLog->Log(JsonString);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TSharedPtr<FJsonObject> MapObject = JsonObject->GetObjectField("Map");
		int width = MapObject->GetIntegerField("width");
		int height = MapObject->GetIntegerField("height");

		GLog->Log("width:" + FString::FromInt(MapObject->GetIntegerField("width")));
		GLog->Log("height:" + FString::FromInt(MapObject->GetIntegerField("height")));

		TArray<TSharedPtr<FJsonValue>> data = MapObject->GetArrayField("data");
		GLog->Log("printing family names...");


		int k = 0;
		int size = 125;
		FActorSpawnParameters spawnParams;
		FloorArray.SetNum(height);

		//GridParent = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector(0, 0, 0), FRotator(0, 0, 0), spawnParams);

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j)
			{
				int block = data[k]->AsNumber();

				switch (block)
				{
				case Wall:
					CreateWall(i, j);
					break;
				case Obstacle:
                    CreateObstacle(i, j);
					break;
				case Floor:
					CreateFloor(i, j);
					break;
				default:
					break;
				}

				++k;
			}
		}
	}
	else
	{
		GLog->Log("couldn't deserialize");
	}
}

void ULocationManager::CreateWall(int & i, int & j)
{
	FVector location(OriginX - BLOCK_SIZE * i, OriginY + BLOCK_SIZE * j, 300);
	FActorSpawnParameters spawnParams;
	AActor* wall = GetWorld()->SpawnActor<AActor>(WallClass, location, FRotator(0, 0, 0), spawnParams);
	AFloor* floor = CreateFloor(i, j);
    floor->OnFloor = OnFloorObj::Wall;
}

void ULocationManager::CreateObstacle(int & i, int & j)
{
    FVector location(OriginX - BLOCK_SIZE * i, OriginY + BLOCK_SIZE * j, 300);
    FActorSpawnParameters spawnParams;
    AActor* obstacle = GetWorld()->SpawnActor<AActor>(ObstacleClass, location, FRotator(0, 0, 0), spawnParams);
    AFloor* floor = CreateFloor(i, j);
    floor->OnFloor = OnFloorObj::Destructable;
}

AFloor* ULocationManager::CreateFloor(int & i, int & j)
{
	FVector location(OriginX - BLOCK_SIZE * i, OriginY + BLOCK_SIZE * j, 200);
	FActorSpawnParameters spawnParams;
	AFloor* floor = GetWorld()->SpawnActor<AFloor>(FloorClass, location, FRotator(0, 0, 0), spawnParams);
	floor->Row = i;
	floor->Column = j;
	FloorArray[i].Array.Add(floor);
    return floor;
}

AActor * ULocationManager::CreateBomb(int& i, int& j)
{
	FVector location(OriginX - BLOCK_SIZE * i, OriginY + BLOCK_SIZE * j, 300);
	FActorSpawnParameters spawnParams;
	AActor* bomb = GetWorld()->SpawnActor<AActor>(BombClass, location, FRotator(0, 0, 0), spawnParams);
	AFloor* floor = FloorArray[i].Array[j];
	floor->ActorOnFloor = bomb;
	return bomb;
}