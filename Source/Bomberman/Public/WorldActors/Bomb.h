#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destructible.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor, public IDestructible
{
	GENERATED_BODY()
	
public:	
	ABomb();

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Destruct() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComp;
};
