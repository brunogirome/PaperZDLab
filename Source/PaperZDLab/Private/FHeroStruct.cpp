// Fill out your copyright notice in the Description page of Project Settings.

#include "FHeroStruct.h"

FHeroStruct::FHeroStruct()
{
}

FHeroStruct::FHeroStruct(int32 id, FString name, FString description, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strength, int32 agility, int32 inteligence, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, float strengthScale, float agilityScale, float inteligenceScale, float physicalDamageScale, float magicDamageScale, float physicalDefenseScale, float magicDefenseScale, float hpScale, float manaScale, float speedScale, float evasionScale, float staminaScale)
		: FCombatActorStruct(id, name, description, HERO, combatType, element, strength, agility, inteligence, hpBase, manaBase, speedBase, evasionBase, staminaBase, physicalDamageBase, magicDamageBase, physicalDefenseBase, magicDefenseBase)
{
	this->StrengthScale = strengthScale;
	this->AgilityScale = agilityScale;
	this->InteligenceScale = inteligenceScale;
	this->PhysicalDamageScale = physicalDamageScale;
	this->MagicDamageScale = magicDamageScale;
	this->PhysicalDefenseScale = physicalDefenseScale;
	this->MagicDefenseScale = magicDefenseScale;
	this->HpScale = hpScale;
	this->ManaScale = manaScale;
	this->SpeedScale = speedScale;
	this->EvasionScale = evasionScale;
	this->StaminaScale = staminaScale;
}
