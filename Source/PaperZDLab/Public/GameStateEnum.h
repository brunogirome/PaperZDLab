#pragma once

#include "CoreMinimal.h"
#include "GameStateEnum.generated.h"

UENUM(BlueprintType)
enum GameStateEnum
{
  OVERWORLD,
  BATTLE,
  MENU,
  PAUSE
};