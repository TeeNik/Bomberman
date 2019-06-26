#include "Bomb.h"

ABomb::ABomb()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MeshComp;
}

void ABomb::Destruct()
{
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
}