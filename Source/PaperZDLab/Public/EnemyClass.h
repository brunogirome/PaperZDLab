// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatActorClass.h"

#include "EnemyStruct.h"

#include "EnemyClass.generated.h"

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
	int32 XpDrop;

	UEnemyClass();

	void Init(FEnemyStruct *enemyStructPointerParam, UMyGameInstance *myGameInstance);
};
