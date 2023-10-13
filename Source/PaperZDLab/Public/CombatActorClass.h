// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "CombatActorStruct.h"

#include "CombatActorClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UCombatActorClass : public UObject
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

	int32 calculateAttribute(int32 baseValue, float multiplier, int32 combatTypeValue, TEnumAsByte<CombatTypeEnum> combatTypeBonus, float buffValue = 0);

protected:
	void init(FCombatActorStruct *combatActorStructPointer);

public:
	FCombatActorStruct *CombatActorStructPointer;

	UPROPERTY(BlueprintReadWrite)
	int32 Strength;

	UPROPERTY(BlueprintReadWrite)
	int32 Agility;

	UPROPERTY(BlueprintReadWrite)
	int32 Inteligence;

	UPROPERTY(BlueprintReadWrite)
	int32 PhysicalDamage;

	UPROPERTY(BlueprintReadWrite)
	int32 MagicDamage;

	UPROPERTY(BlueprintReadWrite)
	int32 PhysicalDefense;

	UPROPERTY(BlueprintReadWrite)
	int32 MagicDefense;

	UPROPERTY(BlueprintReadWrite)
	int32 Hp;

	UPROPERTY(BlueprintReadWrite)
	int32 Mana;

	UPROPERTY(BlueprintReadWrite)
	int32 Speed;

	UPROPERTY(BlueprintReadWrite)
	int32 Evasion;

	UPROPERTY(BlueprintReadWrite)
	int32 Stamina;

	UPROPERTY(BlueprintReadWrite)
	int32 HpCurrent;

	UPROPERTY(BlueprintReadWrite)
	int32 ManaCurrent;

	UCombatActorClass();

	UFUNCTION(BlueprintCallable)
	void calculateStats();

	UFUNCTION(BluePrintCallable)
	bool IsDead();

	UFUNCTION(BluePrintCallable)
	FCombatActorStruct GetActorStruct();

	UFUNCTION(BluePrintCallable)
	void TakeDamage(int32 amount);
};
