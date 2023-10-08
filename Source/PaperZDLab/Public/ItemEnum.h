#pragma once

#include "CoreMinimal.h"
#include "SpellEnum.generated.h"

UENUM(BlueprintType)
enum SpellEnum
{
  DAMAGE UMETA(DisplayName = "DAMAGE"),
  BUFF UMETA(DisplayName = "BUFF"),
  SUPPORT UMETA(DisplayName = "SUPPORT"),
  HEALING UMETA(DisplayName = "HEALING")
};