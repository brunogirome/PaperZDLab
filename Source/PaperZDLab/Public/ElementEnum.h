#pragma once

#include "CoreMinimal.h"
#include "ElementEnum.generated.h"

UENUM(BlueprintType)
enum ElementEnum
{
  FIRE UMETA(DisplayName = "FIRE"),
  WATER UMETA(DisplayName = "WATER"),
  EARTH UMETA(DisplayName = "EARTH"),
  WIND UMETA(DisplayName = "WIND"),
  LIGHT UMETA(DisplayName = "LIGHT"),
  DARK UMETA(DisplayName = "DARK")
};