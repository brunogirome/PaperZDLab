// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatActorClass.h"

int32 UCombatActorClass::calculateAttribute(int32 baseValue, float multiplier, int32 combatTypeValue, TEnumAsByte<CombatTypeEnum> combatTypeBonus, float buffValue)
{
    const int32 typeBonus = this->CombatActorStruct.CombatType == combatTypeBonus ? 2 : 1;

    float convertedBuffValue = 1 + buffValue;

    float combatTypeBonusValue = multiplier * combatTypeValue * typeBonus;

    return (int32)round((baseValue + combatTypeBonusValue) * convertedBuffValue);
}

UCombatActorClass::UCombatActorClass() {}

UCombatActorClass::UCombatActorClass(FCombatActorStruct combatActorStruct)
{
    this->CombatActorStruct = combatActorStruct;

    this->calculateStats();
}

void UCombatActorClass::calculateStats()
{
    this->Hp = calculateAttribute(this->CombatActorStruct.HpBase, this->HP_BONUS, this->Strength, STRENGTH);

    this->Mana = calculateAttribute(this->CombatActorStruct.ManaBase, this->MANA_BONUS, this->Inteligence, INTELIGENCE);

    this->Speed = calculateAttribute(this->CombatActorStruct.SpeedBase, this->SPEED_BONUS, this->Agility, AGILITY);

    this->Evasion = calculateAttribute(this->CombatActorStruct.EvasionBase, this->EVASION_BONUS, this->Agility, AGILITY);

    this->Stamina = calculateAttribute(this->CombatActorStruct.StaminaBase, this->STAMINA_BONUS, this->Agility, AGILITY);

    this->PhysicalDamage = calculateAttribute(this->CombatActorStruct.PhysicalDamageBase, this->PHYSICAL_DAMAGE_BONUS, this->Strength, STRENGTH);

    this->MagicDamage = calculateAttribute(this->CombatActorStruct.MagicDamageBase, this->MAGIC_DAMAGE_BONUS, this->Inteligence, INTELIGENCE);

    this->PhysicalDefense = calculateAttribute(this->CombatActorStruct.PhysicalDefenseBase, this->PHYSICAL_DEFENSE_BONUS, this->Strength, STRENGTH);

    this->MagicDefense = calculateAttribute(this->CombatActorStruct.MagicDefenseBase, this->MAGIC_DEFENSE_BONUS, this->Inteligence, INTELIGENCE);
}

bool UCombatActorClass::isDead()
{
    return this->HpCurrent <= 0;
}
