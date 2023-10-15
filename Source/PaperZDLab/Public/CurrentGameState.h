#pragma once

#include "CoreMinimal.h"
#include "CurrentGameState.generated.h"

UENUM(BlueprintType)
enum CurrentGameState
{
  OVERWORLD,
  BATTLE,
  MENU,
  PAUSE
};