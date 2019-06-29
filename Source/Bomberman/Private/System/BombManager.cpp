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
        AFloor* floor = FloorArray[i].Array[col];
        floor->OnExplosion();
        OnFloorObj onFloor = floor->OnFloor;
        if (GetOwner()->Role == ROLE_Authority) {
            floor->IsExpoding = true;
        }
        if (onFloor == OnFloorObj::Wall || onFloor == OnFloorObj::Destructable) {
            break;
        }
    }

    for (int i = row + 1; i < endI; ++i)
    {
        AFloor* floor = FloorArray[i].Array[col];
        OnFloorObj onFloor = floor->OnFloor;
        floor->OnExplosion();
        if (GetOwner()->Role == ROLE_Authority) {
            floor->IsExpoding = true;
        }
        if (onFloor == OnFloorObj::Wall || onFloor == OnFloorObj::Destructable) {
            break;
        }
    }

    for (int j = col; j >= startJ; --j)
    {
        AFloor* floor = FloorArray[row].Array[j];
        OnFloorObj onFloor = floor->OnFloor;
        floor->OnExplosion();
        if (GetOwner()->Role == ROLE_Authority) {
            floor->IsExpoding = true;
        }
        if (onFloor == OnFloorObj::Wall || onFloor == OnFloorObj::Destructable) {
            break;
        }
    }

    for (int j = col + 1; j < endJ; ++j)
    {
        AFloor* floor = FloorArray[row].Array[j];
        OnFloorObj onFloor = floor->OnFloor;
        floor->OnExplosion();
        if (GetOwner()->Role == ROLE_Authority) {
            floor->IsExpoding = true;
        }
        if (onFloor == OnFloorObj::Wall || onFloor == OnFloorObj::Destructable) {
            break;
        }
    }
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
