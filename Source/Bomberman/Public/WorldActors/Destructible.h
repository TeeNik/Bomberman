#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destructible.generated.h"

UCLASS()
class BOMBERMAN_API ADestructible : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestructible();

	void Destruct();

protected:
	virtual void BeginPlay() override;
};
