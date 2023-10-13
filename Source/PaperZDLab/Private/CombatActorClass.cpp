// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatActorClass.h"

int32 UCombatActorClass::calculateAttribute(int32 baseValue, float multiplier, int32 combatTypeValue, TEnumAsByte<CombatTypeEnum> combatTypeBonus, float buffValue)
{
    const int32 typeBonus = this->CombatActorStructPointer->CombatType == combatTypeBonus ? 2 : 1;

    float convertedBuffValue = 1 + buffValue;

    float combatTypeBonusValue = multiplier * combatTypeValue * typeBonus;

    return (int32)round((baseValue + combatTypeBonusValue) * convertedBuffValue);
}

UCombatActorClass::UCombatActorClass() {}

void UCombatActorClass::init(FCombatActorStruct *combatActorStructPointer)
{
    this->CombatActorStructPointer = combatActorStructPointer;

    this->calculateStats();

    this->HpCurrent = this->Hp;

    this->ManaCurrent = this->Mana;
}

void UCombatActorClass::calculateStats()
{
    this->Hp = calculateAttribute(this->CombatActorStructPointer->HpBase, this->HP_BONUS, this->Strength, STRENGTH);

    this->Mana = calculateAttribute(this->CombatActorStructPointer->ManaBase, this->MANA_BONUS, this->Inteligence, INTELIGENCE);

    this->Speed = calculateAttribute(this->CombatActorStructPointer->SpeedBase, this->SPEED_BONUS, this->Agility, AGILITY);

    this->Evasion = calculateAttribute(this->CombatActorStructPointer->EvasionBase, this->EVASION_BONUS, this->Agility, AGILITY);

    this->Stamina = calculateAttribute(this->CombatActorStructPointer->StaminaBase, this->STAMINA_BONUS, this->Agility, AGILITY);

    this->PhysicalDamage = calculateAttribute(this->CombatActorStructPointer->PhysicalDamageBase, this->PHYSICAL_DAMAGE_BONUS, this->Strength, STRENGTH);

    this->MagicDamage = calculateAttribute(this->CombatActorStructPointer->MagicDamageBase, this->MAGIC_DAMAGE_BONUS, this->Inteligence, INTELIGENCE);

    this->PhysicalDefense = calculateAttribute(this->CombatActorStructPointer->PhysicalDefenseBase, this->PHYSICAL_DEFENSE_BONUS, this->Strength, STRENGTH);

    this->MagicDefense = calculateAttribute(this->CombatActorStructPointer->MagicDefenseBase, this->MAGIC_DEFENSE_BONUS, this->Inteligence, INTELIGENCE);
}

bool UCombatActorClass::IsDead()
{
    return this->HpCurrent <= 0;
}

FCombatActorStruct UCombatActorClass::GetActorStruct()
{
    return *this->CombatActorStructPointer;
}

void UCombatActorClass::TakeDamage(int32 amount)
{
    int32 damageTaken = amount > this->HpCurrent ? this->HpCurrent : amount;

    this->HpCurrent -= damageTaken;
}
