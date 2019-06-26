#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

class UBoxComponent;
class IDestructible;

enum class OnFloorObj {
	Player,
	Wall,
	Destructable,
	Pickup,
	Bomb
};

//Floor is a grid element
//it knows which player stands on it or bomb/pickup is on it and floor
//messages them on bomb explosion

UCLASS(Blueprintable, ClassGroup = (Custom))
class BOMBERMAN_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloor();

	UPROPERTY()
	int Row;

	UPROPERTY()
	int Column;

	UPROPERTY()
	AActor* ActorOnFloor;

	UFUNCTION(BlueprintImplementableEvent)
	void OnExplosion();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* PlayerInteractionCollider;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
