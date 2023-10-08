#pragma once

#include "CoreMinimal.h"
#include "CombatTypeEnum.generated.h"

UENUM(BlueprintType)
enum CombatTypeEnum
{
  STRENGTH UMETA(DisplayName = "STRENGTH"),
  AGILITY UMETA(DisplayName = "AGILITY"),
  INTELIGENCE UMETA(DisplayName = "INTELIGENCE")
};