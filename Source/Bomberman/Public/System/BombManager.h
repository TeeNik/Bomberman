#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BombManager.generated.h"

class AFloor;

//BombManager spawns and explodes bombs

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API UBombManager : public USceneComponent
{
	GENERATED_BODY()

public:	
	UBombManager();

	void SetBomb(AFloor* floor);



protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void ExplodeBomb(int row, int col);
};
