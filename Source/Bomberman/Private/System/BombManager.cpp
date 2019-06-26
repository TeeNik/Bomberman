#include "BombManager.h"
#include "Engine/Public/TimerManager.h"
#include "Floor.h"
#include "LocationManager.h"
#include "BombermanGameMode.h"
#include "Bomb.h"

UBombManager::UBombManager()
{

}

void UBombManager::BeginPlay()
{
	Super::BeginPlay();

}

void UBombManager::ExplodeBomb(int row, int col, AActor* bomb)
{
    ABombermanGameMode* GM = Cast<ABombermanGameMode>(GetWorld()->GetAuthGameMode());

	bomb->Destroy();

	const TArray<FFloorArray> FloorArray = GM->GetLocationManager()->GetFloorArray();

	const int radius = 4;

	int startI = FMath::Max(0, row - radius);
	int startJ = FMath::Max(0, col - radius);

	int endI = FMath::Min(FloorArray.Num(), row + radius + 1);
	int endJ = FMath::Min(FloorArray[0].Array.Num(), col + radius + 1);

	GLog->Log("Explode at: " + FString::FromInt(row) + " " + FString::FromInt(col));
	GLog->Log("I edges: " + FString::FromInt(startI) + " " + FString::FromInt(endI));
	GLog->Log("J edges: " + FString::FromInt(startJ) + " " + FString::FromInt(endJ));


	for (int i = startI; i < endI; ++i) {
		AFloor* floor = FloorArray[i].Array[col];
		floor->OnExplosion();
	}

	for (int j = startJ; j < endJ; ++j) {
		AFloor* floor = FloorArray[row].Array[j];
		floor->OnExplosion();
	}

}

void UBombManager::SetBomb(AFloor * floor)
{
	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate;
    int row = floor->Row;
    int col = floor->Column;

	ABombermanGameMode* GM = Cast<ABombermanGameMode>(GetWorld()->GetAuthGameMode());
	AActor* bomb = GM->GetLocationManager()->CreateBomb(row, col);

	timerDelegate.BindLambda([=]() {
		GLog->Log("Explode...");
		ExplodeBomb(row, col, bomb);
	});
	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, 3.f, false);

}
