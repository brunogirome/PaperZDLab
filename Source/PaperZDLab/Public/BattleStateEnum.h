#pragma once

#include "CoreMinimal.h"
#include "BattleStateEnum.generated.h"

UENUM(BlueprintType)
enum BattleStateEnum
{
  START_STEP,
  END_OF_THE_TURN,
  END_OF_THE_BATTLE,

  HERO_TURN,
  ENEMY_TURN,
  CONFUSED_TURN,

  SELECT_TARGET,
  ATTACK_DECISION,
  SELECT_SPELL,
  SELECT_ITEM,

  PHYSICAL_ATTACK,
  SPELL_CAST,
  ITEM_CAST,
  DEFENDING,
  AUTO_ATTACK_DECISION,

  TRYING_TO_ESCAPE
};