#pragma once

#include "CoreMinimal.h"
#include "ActorTypeEnum.generated.h"

UENUM(BlueprintType)
enum ActorTypeEnum
{
  HERO UMETA(DisplayName = "HERO"),
  ENEMY UMETA(DisplayName = "ENEMY")
};