// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellClass.h"

void USpellClass::Init(FSpellStruct *spellStructPointer)
{
    this->Name = spellStructPointer->Name;

    this->Description = spellStructPointer->Description;

    this->ManaCost = spellStructPointer->ManaCost;

    this->SpellType = spellStructPointer->SpellType;

    this->BuffType = spellStructPointer->BuffType;

    this->Element = spellStructPointer->Element;

    this->PartyBuffType = spellStructPointer->PartyBuffType;

    this->Amount = spellStructPointer->Amount;

    this->Round = spellStructPointer->Round;

    this->RemainingRounds = this->Round + 1;

    this->Multiplier = spellStructPointer->Multiplier;
}

uint8 USpellClass::GetRoundsForCasting()
{
    return this->Round + 1;
}

void USpellClass::ResetRounds()
{
    this->RemainingRounds = this->GetRoundsForCasting();
}

void USpellClass::IncreaseRounds(uint8 amount)
{
    this->RemainingRounds += amount;
}

void USpellClass::DecreaseRounds(uint8 amount)
{
    this->RemainingRounds -= amount;

    if (this->RemainingRounds < 0)
    {
        this->RemainingRounds = 0;
    }
}

USpellClass::USpellClass() {}
