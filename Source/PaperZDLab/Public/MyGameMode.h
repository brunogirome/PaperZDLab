// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "ItemClass.h"

#include "BattleStateEnum.h"

#include "MyGameMode.generated.h"

class UMyGameInstance;

class UBattleManager;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	// const float DEFENDING_DAMAGE_REDUCTION = 0.75f;

	// const float ESCAPE_CHANCE = 0.85f;

	// TArray<UCombatActorStats *> attackOrder;

	UMyGameInstance *gameInstance;

	// int32 turnCurrent;

	// int32 turnSize;

	// int32 currentActorPointer;

	// bool alreadyAttacked;

	// bool victory;

	// bool gameOver;

	// bool escaped;

	// float getDefendingDamageReduction();

	// void startStep();

	// void physicalDamage();

	// void castSpell();

	// void castSpellDamage();

	// void castItem();

	// void enemyTurn();

	// void endOfTheTurn();

	// void tryToEscape();

	// void incrementActorPointer();

	// TArray<APawn *> actorsPointers;

public:
	// TArray<UHeroStats *> *HeroParty;

	// TArray<UEnemyStats *> EnemyParty;

	// TArray<FActiveBuffStruct> ActivePartyBuffs;

	// TEnumAsByte<BattleStateEnum> BattleState;

	// TEnumAsByte<BattleStateEnum> LastBattleState;

	// UCombatActorStats *TargetActor;

	// UCombatActorStats *CurrentActor;

	// USpellClass *CastedSpell;

	// UItemClass *SelectedItem;

	// uint8 AttackStrengthChoice;

	// uint8 CastedSpellPositon;

	// bool AlreadyAttacked;
	UBattleManager *CurrentBattle;

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartBattle(TArray<FName> enemies);

	// UFUNCTION(BlueprintCallable)
	// virtual void Tick(float DeltaSeconds) override;

	// float GetActorAccuracyByStrength(uint8 level);

	// void StartBattle(TArray<FName> enemyPartyNames);

	// void SetBattleState(BattleStateEnum newState);

	AMyGameMode();

	// Debug functions
	// UFUNCTION(BlueprintCallable)
	// void PrintSort();

	// UFUNCTION(BlueprintCallable)
	// void PrintNames();
};
