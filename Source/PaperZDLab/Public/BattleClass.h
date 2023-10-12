// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"

#include "HeroClass.h"
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

	void IncrementActorPointer();

public:
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<BattleStateEnum> CurrentState;

	TArray<UHeroClass *> *Party;

	TArray<UEnemyClass *> EnemyParty;

	TArray<ActorAttackOrder> attackOrder;

	int32 CurrentActorPointer = 0;

	UCombatActorClass *currentActor;

	ABattleClass();

	UFUNCTION(BlueprintCallable)
	void Init(TArray<FName> enemyNames);

	UFUNCTION(BlueprintCallable)
	void SortTurn();

	// Debug functions
	UFUNCTION(BlueprintCallable)
	void PrintSort();

	UFUNCTION(BlueprintCallable)
	void PrintNames();
};
