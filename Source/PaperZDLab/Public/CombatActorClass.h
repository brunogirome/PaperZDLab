// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FCombatActorStruct.h"

#include "CombatActorClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class UCombatActorClass : public UObject
{
	GENERATED_BODY()

	const int PHYSICAL_DAMAGE_BONUS = 1.25f;
	const int PHYSICAL_DEFENSE_BONUS = 0.25f;
	const int HP_BONUS = 2.5f;

	const int MAGIC_DAMAGE_BONUS = 1.8f;
	const int MAGIC_DEFENSE_BONUS = 0.35f;
	const int MANA_BONUS = 2.5f;

	const int SPEED_BONUS = 0.5f;
	const int EVASION_BONUS = 0.5f;
	const int STAMINA_BONUS = 0.25f;

public:
	UPROPERTY(BlueprintReadOnly)
	FCombatActorStruct CombatActorStruct;

	UPROPERTY(BlueprintReadOnly)
	int32 Strength;

	UPROPERTY(BlueprintReadOnly)
	int32 Agility;

	UPROPERTY(BlueprintReadOnly)
	int32 Inteligence;

	UPROPERTY(BlueprintReadOnly)
	int32 PhysicalDamage;

	UPROPERTY(BlueprintReadOnly)
	int32 MagicDamage;

	UPROPERTY(BlueprintReadOnly)
	int32 PhysicalDefense;

	UPROPERTY(BlueprintReadOnly)
	int32 MagicDefense;

	UPROPERTY(BlueprintReadOnly)
	int32 Hp;

	UPROPERTY(BlueprintReadOnly)
	int32 Mana;

	UPROPERTY(BlueprintReadOnly)
	int32 Speed;

	UPROPERTY(BlueprintReadOnly)
	int32 Evasion;

	UPROPERTY(BlueprintReadOnly)
	int32 Stamina;

	UPROPERTY(BlueprintReadOnly)
	int32 HpCurrent;

	UPROPERTY(BlueprintReadOnly)
	int32 ManaCurrent;

	UCombatActorClass();

	// UCombatActorClass(FCombatActorStruct combatActorStruct);
	// UPROPERTY(BluePrintCallable)
	// bool IsDead();

	// UPROPERTY(BluePrintCallable)
	// void Heal(int32 amount);

	// UPROPERTY(BluePrintCallable)
	// void CalculateStatus();
};
