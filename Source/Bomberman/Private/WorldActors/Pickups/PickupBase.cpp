#include "PickupBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Utils/UtilsLibrary.h"

APickupBase::APickupBase()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetVisibility(true);
	BoxComp->SetupAttachment(RootComponent);

}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}

void APickupBase::Collect()
{

}