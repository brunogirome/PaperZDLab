#include "CombatActor.h"

FCombatActor::FCombatActor()
{
}

FCombatActor::FCombatActor(int32 id, FString name, TEnumAsByte<TypeOfActorEnum> typeOfActor, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strength, int32 agility, int32 inteligence, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase)
{
    this->Id = id;
    this->Name = name;
    this->TypeOfActor = typeOfActor;
    this->CombatType = combatType;
    this->Element = element;
    this->Strength = strength;
    this->Agility = agility;
    this->Inteligence = inteligence;
    this->HpBase = hpBase;
    this->ManaBase = manaBase;
    this->SpeedBase = speedBase;
    this->EvasionBase = evasionBase;
    this->StaminaBase = staminaBase;
    this->PhysicalDamageBase = physicalDamageBase;
    this->MagicDamageBase = magicDamageBase;
    this->PhysicalDefenseBase = physicalDefenseBase;
    this->MagicDefenseBase = magicDefenseBase;
}