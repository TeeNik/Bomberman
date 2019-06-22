#include "Floor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Utils/UtilsLibrary.h"

AFloor::AFloor()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetVisibility(true);
	BoxComp->SetupAttachment(RootComponent);

	PlayerInteractionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollider"));
	PlayerInteractionCollider->SetVisibility(true);
	PlayerInteractionCollider->SetupAttachment(RootComponent);
}

void AFloor::BeginPlay()
{
	Super::BeginPlay();

	//PlayerInteractionCollider->OnComponentBeginOverlap.AddDynamic(this, &AFloor::OnBeginOverlap);

	
}

void AFloor::OnBeginOverlap(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	GLog->Log("Overlap");
	if (otherActor->ActorHasTag(UtilsLibrary::PlayerTag)) {
		GLog->Log("Player is on " + GetName());
	}
}
