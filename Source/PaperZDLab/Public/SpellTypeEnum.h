#pragma once

#include "CoreMinimal.h"
#include "SpellTypeEnum.generated.h"

UENUM(BlueprintType)
enum SpellTypeEnum
{
  DAMAGE,
  BUFF,
  SUPPORT,
  HEALING
};