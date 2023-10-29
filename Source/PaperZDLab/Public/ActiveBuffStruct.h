// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellClass.h"

#include "ActiveBuffStruct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FActiveBuffStruct
{
  GENERATED_BODY()

  uint8 RemainingRounds;

  bool IsBuffExpired();

  void DecreaseRounds(uint8 amount = 1);

  void IncreaseRounds(uint8 amount = 1);

  FActiveBuffStruct(USpellClass *spellClassPointer);

  // friend class UCombatActorClass;

  // friend class UMyGameModeClass;

  USpellClass *SpellPointer;
  // private:

  FActiveBuffStruct();
};
