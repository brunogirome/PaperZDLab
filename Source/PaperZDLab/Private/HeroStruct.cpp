// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroStruct.h"

FHeroStruct::FHeroStruct() {}

FHeroStruct::FHeroStruct(FHeroStruct *FHeroStructPointer, int32 level)
	: FCombatActorStruct(FHeroStructPointer)
{
	this->StrengthScale = FHeroStructPointer->StrengthScale;
	this->AgilityScale = FHeroStructPointer->AgilityScale;
	this->InteligenceScale = FHeroStructPointer->InteligenceScale;
	this->PhysicalDamageScale = FHeroStructPointer->PhysicalDamageScale;
	this->MagicDamageScale = FHeroStructPointer->MagicDamageScale;
	this->PhysicalDefenseScale = FHeroStructPointer->PhysicalDefenseScale;
	this->MagicDefenseScale = FHeroStructPointer->MagicDefenseScale;
	this->HpScale = FHeroStructPointer->HpScale;
	this->ManaScale = FHeroStructPointer->ManaScale;
	this->SpeedScale = FHeroStructPointer->SpeedScale;
	this->EvasionScale = FHeroStructPointer->EvasionScale;
	this->StaminaScale = FHeroStructPointer->StaminaScale;

	levelUp(level);
}

FHeroStruct::FHeroStruct(int32 id, FString name, FString description, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strength, int32 agility, int32 inteligence, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, float strengthScale, float agilityScale, float inteligenceScale, float physicalDamageScale, float magicDamageScale, float physicalDefenseScale, float magicDefenseScale, float hpScale, float manaScale, float speedScale, float evasionScale, float staminaScale, int32 level)
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

	levelUp(level);
}

void FHeroStruct::levelUp(int32 level)
{
	this->StrengthBase *= (1 + (this->StrengthScale * level));
	this->AgilityBase *= (1 + (this->AgilityScale * level));
	this->InteligenceBase *= (1 + (this->InteligenceScale * level));
	this->PhysicalDamageScale *= (1 + (this->PhysicalDamageScale * level));
	this->MagicDamageScale *= (1 + (this->MagicDamageScale * level));
	this->PhysicalDefenseScale *= (1 + (this->PhysicalDefenseScale * level));
	this->MagicDefenseBase *= (1 + (this->MagicDefenseScale * level));
	this->HpBase *= (1 + (this->HpScale * level));
	this->ManaBase *= (1 + (this->ManaScale * level));
	this->SpeedScale *= (1 + (this->SpeedScale * level));
	this->EvasionBase *= (1 + (this->EvasionScale * level));
	this->StaminaBase *= (1 + (this->StaminaScale * level));
}
