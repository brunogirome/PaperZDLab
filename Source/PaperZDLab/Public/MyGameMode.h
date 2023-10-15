// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "HeroClass.h"
#include "EnemyClass.h"

#include "BattleStateEnum.h"

#include "MyGameMode.generated.h"

struct ActorAttackOrder
{
	int32 Position;

	int32 Speed;

	bool IsDead;

	FString Name;

	TEnumAsByte<TypeOfActorEnum> TypeOfActor;

	ActorAttackOrder(int32 position, UCombatActorClass *actorClass);
};

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TArray<ActorAttackOrder> attackOrder;

	UCombatActorClass *currentActor;

	int32 turnSize;

	int32 CurrentActorPointer = 0;

	void IncrementActorPointer();

public:
	TArray<UHeroClass *> *HeroParty;

	TArray<UEnemyClass *> EnemyParty;

	TEnumAsByte<BattleStateEnum> BattleState;

	UDataTable *EnemiesDataTable;

	UFUNCTION(BlueprintCallable)
	void StartBattle(TArray<FName> enemyPartyNames);

	UFUNCTION(BlueprintCallable)
	void SortTurn();

	AMyGameMode();

	// Debug functions
	UFUNCTION(BlueprintCallable)
	void PrintSort();

	UFUNCTION(BlueprintCallable)
	void PrintNames();
};
