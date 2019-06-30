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

	const int radius = 2;

	int startI = FMath::Max(0, row - radius);
	int startJ = FMath::Max(0, col - radius);

	int endI = FMath::Min(FloorArray.Num(), row + radius + 1);
	int endJ = FMath::Min(FloorArray[0].Array.Num(), col + radius + 1);

	GLog->Log("Explode at: " + FString::FromInt(row) + " " + FString::FromInt(col));
	GLog->Log("I edges: " + FString::FromInt(startI) + " " + FString::FromInt(endI));
	GLog->Log("J edges: " + FString::FromInt(startJ) + " " + FString::FromInt(endJ));


    for (int i = row; i >= startI; --i)
    {
        if (ProduceExplosionOnFloor(FloorArray[i].Array[col])) {
            break;
        }
    }

    for (int i = row + 1; i < endI; ++i)
    {
        if (ProduceExplosionOnFloor(FloorArray[i].Array[col])) {
            break;
        }
    }

    for (int j = col; j >= startJ; --j)
    {
        if (ProduceExplosionOnFloor(FloorArray[row].Array[j])) {
            break;
        }
    }

    for (int j = col + 1; j < endJ; ++j)
    {
        if (ProduceExplosionOnFloor(FloorArray[row].Array[j])) {
            break;
        }
    }
}

bool UBombManager::ProduceExplosionOnFloor(AFloor* floor)
{
    OnFloorObj onFloor = floor->OnFloor;
    floor->OnExplosion();
    if (GetOwner()->Role == ROLE_Authority) {
        floor->IsExpoding = true;
        floor->IsExpoding = false;
    }
    if (onFloor == OnFloorObj::Wall || onFloor == OnFloorObj::Destructable) {
        if (IsValid(floor->ActorOnFloor)) {
            floor->ActorOnFloor->Destroy();
        }
        return true;
    }
    if (IsValid(floor->ActorOnFloor)) {
        floor->ActorOnFloor->Destroy();
    }
    return false;
}

void UBombManager::SetBomb(AFloor * floor)
{
    if (!IsValid(floor)) {
        GLog->Log("!IsValid(floor)");
        return;
    }

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
