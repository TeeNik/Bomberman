#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destructible.h"
#include "Obstacle.generated.h"

UCLASS()
class BOMBERMAN_API AObstacle : public AActor, public IDestructible
{
	GENERATED_BODY()
	
public:	
	AObstacle();

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Destruct() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComp;

};
