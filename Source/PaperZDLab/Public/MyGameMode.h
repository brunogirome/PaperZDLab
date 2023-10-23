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

	class UMyGameInstance *gameInstance;

	int32 turnCurrent;

	int32 turnSize;

	int32 currentActorPointer;

	bool alreadyAttacked;

	bool victory;

	bool gameOver;

	void startStep();

	void physicalDamage();

	void castSpell();

	void castSpellDamage();

	void endOfTheTurn();

	void incrementActorPointer();

public:
	TArray<UHeroClass *> *HeroParty;

	TArray<UEnemyClass *> EnemyParty;

	TArray<float> ATTACK_STRENGTH_ACCURACY_BASE;

	TEnumAsByte<BattleStateEnum> BattleState;

	TEnumAsByte<BattleStateEnum> LastBattleState;

	UCombatActorClass *TargetActor;

	UCombatActorClass *CurrentActor;

	USpellClass *CastedSpell;

	uint8 AtackStrengthChoice;

	uint8 CastedSpellPositon;

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void StartBattle(TArray<FName> enemyPartyNames);

	void SetBattleState(BattleStateEnum newState);

	AMyGameMode();

	// Debug functions
	UFUNCTION(BlueprintCallable)
	void PrintSort();

	UFUNCTION(BlueprintCallable)
	void PrintNames();
};
