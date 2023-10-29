#pragma once

#include "CoreMinimal.h"
#include "BuffTypeEnum.generated.h"

UENUM(BlueprintType)
enum BuffTypeEnum
{
  NOT_BUFF,
  PHYSICAL_DAMAGE_BUFF,
  PHYSICAL_DEFENSE_BUFF,
  MAGIC_DAMAGE_BUFF,
  MAGIC_DEFENSE_BUFF,
  SPEED_BUFF,
  STAMINA_BUFF,
  EVASION_BUFF,
  STRENGTH_BUFF,
  AGILITY_BUFF,
  INTELIGENCE_BUFF
};