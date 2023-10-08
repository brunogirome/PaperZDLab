#pragma once

#include "CoreMinimal.h"
#include "ItemEnum.generated.h"

UENUM(BlueprintType)
enum ItemEnum
{
  ARTIFACT_PART UMETA(DisplayName = "ARTIFACT_PART"),
  ARTIFACT UMETA(DisplayName = "ARTIFACT"),
  CONSUMABLE UMETA(DisplayName = "CONSUMABLE"),
  KEY UMETA(DisplayName = "KEY")
};