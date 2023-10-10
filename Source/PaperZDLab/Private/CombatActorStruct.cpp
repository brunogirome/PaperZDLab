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
