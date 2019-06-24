#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldActors/Destructible.h"
#include "PickupBase.generated.h"

class UBoxComponent;

//base class for any pickups

UCLASS()
class BOMBERMAN_API APickupBase : public AActor, public IDestructible
{
	GENERATED_BODY()
	
public:	
	APickupBase();

protected:
	virtual void BeginPlay() override;

	virtual void Collect();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComp;
};
