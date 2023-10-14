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

	UPROPERTY(EditAnywhere)
	float StrengthScale;

	UPROPERTY(EditAnywhere)
	float AgilityScale;

	UPROPERTY(EditAnywhere)
	float InteligenceScale;

	UPROPERTY(EditAnywhere)
	float PhysicalDamageScale;

	UPROPERTY(EditAnywhere)
	float MagicDamageScale;

	UPROPERTY(EditAnywhere)
	float PhysicalDefenseScale;

	UPROPERTY(EditAnywhere)
	float MagicDefenseScale;

	UPROPERTY(EditAnywhere)
	float HpScale;

	UPROPERTY(EditAnywhere)
	float ManaScale;

	UPROPERTY(EditAnywhere)
	float SpeedScale;

	UPROPERTY(EditAnywhere)
	float EvasionScale;

	UPROPERTY(EditAnywhere)
	float StaminaScale;

	FHeroStruct();

	FHeroStruct(FHeroStruct *FHeroStructPointer, int32 level);

	void levelUp(int32 level);
};
