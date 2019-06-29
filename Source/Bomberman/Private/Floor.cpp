#include "Floor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Utils/UtilsLibrary.h"
#include "Destructible.h"
#include "BombermanCharacter.h"
#include "Net/UnrealNetwork.h"

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

    bReplicates = true;
}
/*
void AFloor::OnExplosion()
{
	if (IsValid(ActorOnFloor)) {
		if (ActorOnFloor->GetClass()->ImplementsInterface(UDestructible::StaticClass())) {
			IDestructible* dest = Cast<IDestructible>(ActorOnFloor);
			dest->Destruct();
		}
	}
}*/

void AFloor::BeginPlay()
{
	Super::BeginPlay();

	PlayerInteractionCollider->OnComponentBeginOverlap.AddDynamic(this, &AFloor::OnBeginOverlap);
}

void AFloor::OnRep_IsExploding()
{
    if (IsExpoding == true) {
        OnExplosion();
    }
    IsExpoding = false;
}

void AFloor::OnBeginOverlap(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	GLog->Log("Overlap");
	if (otherActor->ActorHasTag(UtilsLibrary::PlayerTag)) {
		GLog->Log("Player is on " + GetName());
        ABombermanCharacter* character = Cast<ABombermanCharacter>(otherActor);
        character->Floor = this;
	}
}

void AFloor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AFloor, IsExpoding);
}

