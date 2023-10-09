// Fill out your copyright notice in the Description page of Project Settings.

#include "FEnemyStruct.h"

FEnemyStruct::FEnemyStruct()
{
}

FEnemyStruct::FEnemyStruct(int32 id, FString name, FString description, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strength, int32 agility, int32 inteligence, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, int32 xpDrop)
		: FCombatActorStruct(id, name, description, ENEMY, combatType, element, strength, agility, inteligence, hpBase, manaBase, speedBase, evasionBase, staminaBase, physicalDamageBase, magicDamageBase, physicalDefenseBase, magicDefenseBase)
{
	this->XpDrop = xpDrop;
}
