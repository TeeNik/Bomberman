#include "Obstacle.h"

AObstacle::AObstacle()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MeshComp;
    bReplicates = true;
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacle::Destruct()
{
	Destroy();
}