// Fill out your copyright notice in the Description page of Project Settings.

#include "ActiveBuffStruct.h"

bool FActiveBuffStruct::IsBuffExpired()
{
  return this->RemainingRounds <= 0;
}

void FActiveBuffStruct::DecreaseRounds(uint8 amount)
{
  this->RemainingRounds -= amount;

  if (this->RemainingRounds < 0)
  {
    this->RemainingRounds = 0;
  }
}

void FActiveBuffStruct::IncreaseRounds(uint8 amount)
{
  this->RemainingRounds += amount;
}

FActiveBuffStruct::FActiveBuffStruct(USpellClass *spellClassPointer)
{
  this->SpellPointer = spellClassPointer;

  this->RemainingRounds = spellClassPointer->GetRoundsForCasting();
}

FActiveBuffStruct::FActiveBuffStruct() {}
