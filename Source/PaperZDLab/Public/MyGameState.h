// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"

#include "MyGameState.generated.h"

class AHero;

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

	UMyGameInstance *gameInstance;

	AMyGameMode *gameMode;

public:
	UFUNCTION(BlueprintCallable)
	TArray<AHero *> GetPartyMembers();

	// UFUNCTION(BlueprintCallable)
	// TArray<UEnemyStats *> GetEnemyPartyMembers();

	// UFUNCTION(BlueprintCallable)
	// TArray<UItemClass *> GetInventory();

	// UFUNCTION(BlueprintCallable)
	// TArray<float> GetATTACK_STRENGTH_ACCURACY();

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<CurrentGameState> GetCurrentGameState();

	// UFUNCTION(BlueprintCallable)
	// TEnumAsByte<BattleStateEnum> GetLastBattleState();

	// UFUNCTION(BlueprintCallable)
	// TEnumAsByte<BattleStateEnum> GetBattleState();

	// UFUNCTION(BlueprintCallable)
	// TEnumAsByte<SpellTypeEnum> GetSpellCastedType();

	// UFUNCTION(BlueprintCallable)
	// UCombatActorStats *GetCurrentActor();

	// UFUNCTION(BlueprintCallable)
	// UHeroStats *GetHeroByPartyPosition(uint8 position);

	// UFUNCTION(BlueprintCallable)
	// UEnemyStats *GetEnemyByPartyPosition(uint8 position);

	// UFUNCTION(BlueprintCallable)
	// float GetActorAccuracyByStrength(uint8 level);

	// UFUNCTION(BlueprintCallable)
	// bool GetAlreadyAttacked();

	// UFUNCTION(BlueprintCallable)
	// bool IsPartyBuffActive(PartyBuffTypeEnum partyBuffType);

	// UFUNCTION(BlueprintCallable)
	// void StartBattle(TArray<FName> enemiesRowNames);

	// UFUNCTION(BlueprintCallable)
	// void SetAttackStrengthChoice(uint8 choice);

	UFUNCTION(BlueprintCallable)
	void SetCurrentGameMode(CurrentGameState newCurrentGameState);

	// UFUNCTION(BlueprintCallable)
	// void SetBattleState(BattleStateEnum newBattleState);

	// UFUNCTION(BlueprintCallable)
	// void SetEnemyAsTargetByPosition(uint8 enemyPosition);

	// UFUNCTION(BlueprintCallable)
	// void SetHeroAsTargetByName(FString name);

	// UFUNCTION(BlueprintCallable)
	// void CastSpell(uint8 position);

	// UFUNCTION(BlueprintCallable)
	// void SelectItemToConsume(uint8 positonOnInventory);

	// UFUNCTION(BlueprintCallable)
	// void AddItemToInventory(FName itemName, uint8 amount = 1);

	// UFUNCTION(BlueprintCallable)
	// void RemoveItemFromInventory(int32 position);

	// UFUNCTION(BlueprintCallable)
	// void ConsumeItemOnInventory(int32 position, UHeroStats *selectedHero);

	// UFUNCTION(BlueprintCallable)
	// void EquipItem(int32 position, UHeroStats *selectedHero);

	// UFUNCTION(BlueprintCallable)
	// void UnequipItem(int32 position, UHeroStats *selectedHero);

	AMyGameState();
};
