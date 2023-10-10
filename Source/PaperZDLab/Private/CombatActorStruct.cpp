// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatActorStruct.h"

FCombatActorStruct::FCombatActorStruct() {}

FCombatActorStruct::FCombatActorStruct(FCombatActorStruct *FCombatActorStructPointer)
{
  this->Id = FCombatActorStructPointer->Id;
  this->Name = FCombatActorStructPointer->Name;
  this->Description = FCombatActorStructPointer->Description;

  this->TypeOfActor = FCombatActorStructPointer->TypeOfActor;
  this->CombatType = FCombatActorStructPointer->CombatType;
  this->Element = FCombatActorStructPointer->Element;

  this->StrengthBase = FCombatActorStructPointer->StrengthBase;
  this->AgilityBase = FCombatActorStructPointer->AgilityBase;
  this->InteligenceBase = FCombatActorStructPointer->InteligenceBase;

  this->PhysicalDamageBase = FCombatActorStructPointer->PhysicalDamageBase;
  this->MagicDamageBase = FCombatActorStructPointer->MagicDamageBase;
  this->PhysicalDefenseBase = FCombatActorStructPointer->PhysicalDefenseBase;
  this->MagicDefenseBase = FCombatActorStructPointer->MagicDefenseBase;

  this->HpBase = FCombatActorStructPointer->HpBase;
  this->ManaBase = FCombatActorStructPointer->ManaBase;
  this->SpeedBase = FCombatActorStructPointer->SpeedBase;
  this->EvasionBase = FCombatActorStructPointer->EvasionBase;
  this->StaminaBase = FCombatActorStructPointer->StaminaBase;
}

FCombatActorStruct::FCombatActorStruct(int32 id, FString name, FString description, TEnumAsByte<TypeOfActorEnum> typeOfActor, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strengthBase, int32 agilityBase, int32 inteligenceBase, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase)
{
  this->Id = id;
  this->Name = name;
  this->Description = description;

  this->TypeOfActor = typeOfActor;
  this->CombatType = combatType;
  this->Element = element;

  this->StrengthBase = strengthBase;
  this->AgilityBase = agilityBase;
  this->InteligenceBase = inteligenceBase;

  this->PhysicalDamageBase = physicalDamageBase;
  this->MagicDamageBase = magicDamageBase;
  this->PhysicalDefenseBase = physicalDefenseBase;
  this->MagicDefenseBase = magicDefenseBase;

  this->HpBase = hpBase;
  this->ManaBase = manaBase;
  this->SpeedBase = speedBase;
  this->EvasionBase = evasionBase;
  this->StaminaBase = staminaBase;
}
