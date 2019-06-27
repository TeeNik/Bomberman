#include "BombermanGameMode.h"
#include "BombermanCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "LocationManager.h"
#include "BombManager.h"

ABombermanGameMode::ABombermanGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	LocationManager = CreateDefaultSubobject<ULocationManager>(TEXT("LocationManager"));
	RootComponent = LocationManager;

	BombManager = CreateDefaultSubobject<UBombManager>(TEXT("BombManager"));
}

void ABombermanGameMode::BeginPlay()
{
	Super::BeginPlay();

    if (Role == ROLE_Authority) {
        LocationManager->GenerateMap();
    }
}
