// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroStruct.h"

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

FHeroStruct::FHeroStruct() {}