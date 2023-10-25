// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "HeroClass.h"
#include "EnemyClass.h"

#include "BattleStateEnum.h"

#include "MyGameMode.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TArray<UCombatActorClass *> attackOrder;

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

	void enemyTurn();

	void endOfTheTurn();

	void incrementActorPointer();

public:
	TArray<UHeroClass *> *HeroParty;

	TArray<UEnemyClass *> EnemyParty;

	TEnumAsByte<BattleStateEnum> BattleState;

	TEnumAsByte<BattleStateEnum> LastBattleState;

	UCombatActorClass *TargetActor;

	UCombatActorClass *CurrentActor;

	USpellClass *CastedSpell;

	uint8 AttackStrengthChoice;

	uint8 CastedSpellPositon;

	bool AlreadyAttacked;

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Tick(float DeltaSeconds) override;

	float GetActorAccuracyByStrength(uint8 level);

	void StartBattle(TArray<FName> enemyPartyNames);

	void SetBattleState(BattleStateEnum newState);

	AMyGameMode();

	// Debug functions
	UFUNCTION(BlueprintCallable)
	void PrintSort();

	UFUNCTION(BlueprintCallable)
	void PrintNames();
};
