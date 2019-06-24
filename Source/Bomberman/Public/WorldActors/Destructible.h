#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Destructible.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UDestructible : public UInterface 
{
	GENERATED_BODY()
};


class IDestructible
{
	GENERATED_BODY()
	
public:	
	virtual void Destruct() {}
};
