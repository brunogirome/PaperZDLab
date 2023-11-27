// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "HeroClass.h"
#include "EnemyClass.h"
#include "ItemClass.h"

#include "BattleStateEnum.h"

#include "MyGameMode.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	const float DEFENDING_DAMAGE_REDUCTION = 0.75f;

	const float ESCAPE_CHANCE = 0.85f;

	TArray<UCombatActorClass *> attackOrder;

	class UMyGameInstance *gameInstance;

	int32 turnCurrent;

	int32 turnSize;

	int32 currentActorPointer;

	bool alreadyAttacked;

	bool victory;

	bool gameOver;

	bool escaped;

	float getDefendingDamageReduction();

	void startStep();

	void physicalDamage();

	void castSpell();

	void castSpellDamage();

	void castItem();

	void enemyTurn();

	void endOfTheTurn();

	void tryToEscape();

	void incrementActorPointer();

	TArray<APawn *> actorsPointers;

public:
	TArray<UHeroClass *> *HeroParty;

	TArray<UEnemyClass *> EnemyParty;

	TArray<FActiveBuffStruct> ActivePartyBuffs;

	TEnumAsByte<BattleStateEnum> BattleState;

	TEnumAsByte<BattleStateEnum> LastBattleState;

	UCombatActorClass *TargetActor;

	UCombatActorClass *CurrentActor;

	USpellClass *CastedSpell;

	UItemClass *SelectedItem;

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
