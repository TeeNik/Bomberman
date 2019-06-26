#include "Obstacle.h"

AObstacle::AObstacle()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MeshComp;
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacle::Destruct()
{
	Destroy();
}