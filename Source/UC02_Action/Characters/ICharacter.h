#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class UC02_ACTION_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(FLinearColor InColor) = 0;
};
