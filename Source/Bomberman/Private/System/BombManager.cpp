#include "BombManager.h"
#include "Engine/Public/TimerManager.h"
#include "Floor.h"
#include "LocationManager.h"
#include "BombermanGameMode.h"

UBombManager::UBombManager()
{

}

void UBombManager::BeginPlay()
{
	Super::BeginPlay();

}

void UBombManager::ExplodeBomb(int row, int col)
{
    ABombermanGameMode* GM = Cast<ABombermanGameMode>(GetWorld()->GetAuthGameMode());

	const TArray<FFloorArray> FloorArray = GM->GetLocationManager()->GetFloorArray();

	const int radius = 4;

	int startI = FMath::Max(0, row - radius);
	int startJ = FMath::Max(0, col - radius);

	int endI = FMath::Min(FloorArray.Num(), row + radius);
	int endJ = FMath::Min(FloorArray[0].Array.Num(), col + radius);

	for (int i = startI; i < endI; ++i) {
		AFloor* floor = FloorArray[i].Array[col];
		floor->OnHighlight();
	}

}

void UBombManager::SetBomb(AFloor * floor)
{

	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([&]() {
		GLog->Log("Explode...");
		ExplodeBomb(floor->Row, floor->Column);
	});
	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, 3.f, false);
}
