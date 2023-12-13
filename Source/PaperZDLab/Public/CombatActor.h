// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SpawnnableActor.h"

#include "TypeOfActorEnum.h"

#include "CombatTypeEnum.h"

#include "ElementEnum.h"

#include "CombatActor.generated.h"

class UMyGameInstance;

class USpellClass;

class UItemClass;

struct FCombatActorStruct;

struct FActiveBuffStruct;

struct FEquipamentBuffStruct
{
	int FlatBonus;

	float PercentageBonus;
};

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ACombatActor : public ASpawnnableActor
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

	FCombatActorStruct *CombatActorStructPointer;

protected:
	void initialize(FCombatActorStruct *combatActorStruct);

public:
	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString Description;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<TypeOfActorEnum> TypeOfActor;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<CombatTypeEnum> CombatType;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ElementEnum> Element;

	UPROPERTY(BlueprintReadOnly)
	TArray<FActiveBuffStruct> ActiveBuffs;

	UPROPERTY(BluePrintReadOnly)
	TArray<USpellClass *> Spells;

	UPROPERTY(BluePrintReadOnly)
	TArray<UItemClass *> Equipaments;

	UPROPERTY(BluePrintReadOnly)
	int32 Strength;

	UPROPERTY(BluePrintReadOnly)
	int32 Agility;

	UPROPERTY(BluePrintReadOnly)
	int32 Inteligence;

	UPROPERTY(BluePrintReadOnly)
	int32 PhysicalDamage;

	UPROPERTY(BluePrintReadOnly)
	int32 MagicDamage;

	UPROPERTY(BluePrintReadOnly)
	int32 PhysicalDefense;

	UPROPERTY(BluePrintReadOnly)
	int32 MagicDefense;

	UPROPERTY(BluePrintReadOnly)
	int32 Hp;

	UPROPERTY(BluePrintReadOnly)
	int32 Mana;

	UPROPERTY(BluePrintReadOnly)
	int32 Speed;

	UPROPERTY(BluePrintReadOnly)
	int32 Evasion;

	UPROPERTY(BluePrintReadOnly)
	int32 Stamina;

	UPROPERTY(BluePrintReadOnly)
	int32 HpCurrent;

	UPROPERTY(BluePrintReadOnly)
	int32 ManaCurrent;

	UPROPERTY(BluePrintReadOnly)
	int32 StaminaCurrent;

	UPROPERTY(BluePrintReadOnly)
	float WeakAccuracy;

	UPROPERTY(BluePrintReadOnly)
	float MediumAccuracy;

	UPROPERTY(BluePrintReadOnly)
	float StrongAccuracy;

	UPROPERTY(BluePrintReadOnly)
	bool IsDefending;

	uint8 PositionForEnemyInBattle;

	UFUNCTION(BluePrintCallable)
	bool IsDead();

	UFUNCTION(BlueprintCallable)
	void CalculateStats();

	bool IsOutOfStamina();

	void HealHp(int32 amount);

	void TakeDamage(int32 amount);

	void HealStamina(uint8 amount, bool full = false);

	void ReduceStamina(uint8 amount);

	void UseMana(int32 amount);

	void AddBuff(USpellClass *buffSpell);

	void RemoveBuff(uint8 position);

	ACombatActor();
};
