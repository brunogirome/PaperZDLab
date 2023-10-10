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

	FHeroStruct(FHeroStruct *FHeroStructPointer, int32 level);

	void levelUp(int32 level);
};
