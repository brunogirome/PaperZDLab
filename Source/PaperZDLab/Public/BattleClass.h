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

	int32 turnSize;

	void IncrementActorPointer();

	TArray<UHeroClass *> *Party;

	TArray<ActorAttackOrder> attackOrder;

	int32 CurrentActorPointer = 0;

	UCombatActorClass *currentActor;

public:
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<BattleStateEnum> BattleState;

	UPROPERTY(BluePrintReadOnly)
	TArray<UEnemyClass *> EnemyParty;

	UFUNCTION(BlueprintCallable)
	void Init(TArray<FName> enemyNames);

	UFUNCTION(BlueprintCallable)
	void SortTurn();

	ABattleClass();

	// Debug functions
	UFUNCTION(BlueprintCallable)
	void PrintSort();

	UFUNCTION(BlueprintCallable)
	void PrintNames();
};
