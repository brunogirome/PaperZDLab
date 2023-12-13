// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CombatActor.h"

#include "Enemy.generated.h"

enum EMoveType
{
	WEAK_ATTACK,
	MEDIUM_ATTACK,
	HEAVY_ATTACK,
	CAST_SPELL_MOVESET
};

struct FAttackPatern
{
	EMoveType MoveType;
	uint8 SpellPosition;

	FAttackPatern(EMoveType moveType, uint8 spellPosition = 0)
	{
		this->MoveType = moveType;
		this->SpellPosition = spellPosition;
	}
};

struct FEnemyStruct;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AEnemy : public ACombatActor
{
	GENERATED_BODY()

	FEnemyStruct *EnemyStruct;

public:
	UPROPERTY(BlueprintReadOnly)
	uint8 Position;

	UPROPERTY(BlueprintReadOnly)
	int32 XpDrop;

	TArray<TArray<FAttackPatern>> Movesets;

	AEnemy();

	void Initialize(FEnemyStruct *enemyStruct, uint8 battleInstancePosition = -1);
};
