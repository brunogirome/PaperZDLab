// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatActorStruct.h"

#include "EnemyStruct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FEnemyStruct : public FCombatActorStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 XpDrop;

	FEnemyStruct();
};
