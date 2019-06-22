#include "Destructible.h"

ADestructible::ADestructible()
{

}

void ADestructible::BeginPlay()
{
	Super::BeginPlay();
}

void ADestructible::Destruct()
{
	Destroy();
}

