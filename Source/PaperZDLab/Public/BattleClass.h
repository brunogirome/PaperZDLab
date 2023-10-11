// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"
#include "Engine/DataTable.h"

#include "PartyClass.h"
#include "EnemyClass.h"

#include "BattleStateEnum.h"

#include "BattleClass.generated.h"

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
UCLASS(BlueprintType)
class PAPERZDLAB_API ABattleClass : public AGameStateBase
{
	GENERATED_BODY()

private:
	int32 turnSize;

	

public:
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<BattleStateEnum> CurrentState;

	TArray<UHeroClass *> *Party;

	TArray<UEnemyClass *> EnemyParty;

	TArray<ActorAttackOrder> attackOrder;

	UDataTable *EnemiesDataTable;

	int32 CurrentActorPointer = 0;

	UCombatActorClass *currentActor;

	ABattleClass();

	UFUNCTION(BlueprintCallable)
	TArray<UHeroClass *> GetParty();

	UFUNCTION(BlueprintCallable)
	void Init(UPartyClass *GameParty, TArray<FName> enemiesRowNames);

	UFUNCTION(BlueprintCallable)
	void PrintNames();

	UFUNCTION(BlueprintCallable)
	void SortTurn();

	UFUNCTION(BlueprintCallable)
	void PrintSort();

	UFUNCTION(BlueprintCallable)
	void IncrementActorPointer();
};
