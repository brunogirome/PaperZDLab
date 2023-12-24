// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleManager.generated.h"

class AHero;

class AEnemy;

class UMyGameState;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API UBattleManager : public UObject
{
	GENERATED_BODY()

	TArray<FVector> heroesGoalLocation;

	UMyGameState *gameState;

public:
	TArray<AEnemy*> BattleEnemies;

	TArray<AHero*> *HeroParty;

	void Intialize(TArray<FName> enemies, UMyGameState *myGameStateRef, FVector enemyLocation);

	UBattleManager();
};
