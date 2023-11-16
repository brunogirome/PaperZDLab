// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatActorClass.h"

#include "EnemyStruct.h"

#include "EnemyClass.generated.h"

enum MoveTypeEnum
{
	WEAK_ATTACK,
	MEDIUM_ATTACK,
	HEAVY_ATTACK,
	CAST_SPELL_MOVESET
};

struct AttackPatern
{
	MoveTypeEnum MoveType;
	uint8 SpellPosition;

	AttackPatern(MoveTypeEnum moveType, uint8 spellPosition = 0)
	{
		this->MoveType = moveType;
		this->SpellPosition = spellPosition;
	}
};

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UEnemyClass : public UCombatActorClass
{
	GENERATED_BODY()

	FEnemyStruct *EnemyStructPointer;

public:
	UPROPERTY(BlueprintReadOnly)
	uint8 Position;

	UPROPERTY(BlueprintReadOnly)
	int32 XpDrop;

	TArray<TArray<AttackPatern>> Movesets;

	UEnemyClass();

	void Init(FEnemyStruct *enemyStructPointerParam, UMyGameInstance *myGameInstance, uint8 battleInstancePosition = -1);
};
