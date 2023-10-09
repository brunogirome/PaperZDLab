#pragma once

#include "CoreMinimal.h"
#include "TypeOfActorEnum.generated.h"

UENUM(BlueprintType)
enum TypeOfActorEnum
{
  HERO UMETA(DisplayName = "HERO"),
  ENEMY UMETA(DisplayName = "ENEMY")
};