// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatActorStruct.h"

#include "HeroStruct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FHeroStruct : public FCombatActorStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float StrengthScale;

	UPROPERTY(BlueprintReadOnly)
	float AgilityScale;

	UPROPERTY(BlueprintReadOnly)
	float InteligenceScale;

	UPROPERTY(BlueprintReadOnly)
	float PhysicalDamageScale;

	UPROPERTY(BlueprintReadOnly)
	float MagicDamageScale;

	UPROPERTY(BlueprintReadOnly)
	float PhysicalDefenseScale;

	UPROPERTY(BlueprintReadOnly)
	float MagicDefenseScale;

	UPROPERTY(BlueprintReadOnly)
	float HpScale;

	UPROPERTY(BlueprintReadOnly)
	float ManaScale;

	UPROPERTY(BlueprintReadOnly)
	float SpeedScale;

	UPROPERTY(BlueprintReadOnly)
	float EvasionScale;

	UPROPERTY(BlueprintReadOnly)
	float StaminaScale;

	FHeroStruct();

	FHeroStruct(int32 id, FString name, FString description, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strength, int32 agility, int32 inteligence, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, float strengthScale, float agilityScale, float inteligenceScale, float physicalDamageScale, float magicDamageScale, float physicalDefenseScale, float magicDefenseScale, float hpScale, float manaScale, float speedScale, float evasionScale, float staminaScale);
};
