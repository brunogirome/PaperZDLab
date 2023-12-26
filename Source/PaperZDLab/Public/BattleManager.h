// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleManager.generated.h"

class AHero;

class AEnemy;

class AEnemyLeader;

class UMyGameInstance;

class AMyGameMode;

struct FAIRequestID;

struct FPathFollowingResult;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API UBattleManager : public UObject
{
	GENERATED_BODY()

	UMyGameInstance *gameInstance;

	AMyGameMode *gameMode;

	TArray<AHero *> *heroParty;

	TArray<AEnemy *> enemyParty;

public:
	void Intialize(TArray<FName> enemies, AEnemyLeader *enemyLeader, UMyGameInstance *myGameInstance, AMyGameMode *myGameMode);

	void OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult &Result);

	UBattleManager();
};
