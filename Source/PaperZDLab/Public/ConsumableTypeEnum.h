#pragma once

#include "CoreMinimal.h"
#include "ConsumableTypeEnum.generated.h"

UENUM(BlueprintType)
enum ConsumableTypeEnum
{
  NOT_CONSUMABLE,
  POTION_HP,
  POTION_MANA,
  ELIXIR
};