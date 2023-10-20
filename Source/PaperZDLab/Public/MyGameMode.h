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

	class UMyGameInstance *GameInstance;

	int32 turnSize;

	int32 CurrentActorPointer = 0;

	void startStep();

	void physicalDamage();

	void incrementActorPointer();

public:
	TArray<UHeroClass *> *HeroParty;

	TArray<UEnemyClass *> EnemyParty;

	TArray<uint8> ATTACK_STRENGTH_ACCURACY;

	UCombatActorClass *TargetActor;

	TEnumAsByte<BattleStateEnum> BattleState;

	TEnumAsByte<BattleStateEnum> LastBattleState;

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Tick();

	UFUNCTION(BlueprintCallable)
	void StartBattle(TArray<FName> enemyPartyNames);

	AMyGameMode();

	// Debug functions
	UFUNCTION(BlueprintCallable)
	void PrintSort();

	UFUNCTION(BlueprintCallable)
	void PrintNames();
};
