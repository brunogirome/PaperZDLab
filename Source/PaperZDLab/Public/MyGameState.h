// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "HeroClass.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"

#include "MyGameState.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

	UMyGameInstance *GameInstance;

	AMyGameMode *GameMode;

public:
	UFUNCTION(BlueprintCallable)
	TArray<UHeroClass *> GetPartyMembers();

	UFUNCTION(BlueprintCallable)
	TArray<UEnemyClass *> GetEnemyPartyMembers();

	UFUNCTION(BlueprintCallable)
	TArray<float> GetATTACK_STRENGTH_ACCURACY();

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<CurrentGameState> GetCurrentGameState();

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<BattleStateEnum> GetLastBattleState();

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<BattleStateEnum> GetBattleState();

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<SpellTypeEnum> GetSpellCastedType();

	UFUNCTION(BlueprintCallable)
	UCombatActorClass *GetCurrentActor();

	UFUNCTION(BlueprintCallable)
	UHeroClass *GetHeroByPartyPosition(uint8 position);

	UFUNCTION(BlueprintCallable)
	UEnemyClass *GetEnemyByPartyPosition(uint8 position);

	UFUNCTION(BlueprintCallable)
	float GetActorAccuracyByStrength(uint8 level);

	UFUNCTION(BlueprintCallable)
	bool GetAlreadyAttacked();

	UFUNCTION(BlueprintCallable)
	void StartBattle(TArray<FName> enemiesRowNames);

	UFUNCTION(BlueprintCallable)
	void SetAtackStrengthChoice(uint8 choice);

	UFUNCTION(BlueprintCallable)
	void SetCurrentGameMode(CurrentGameState newCurrentGameState);

	UFUNCTION(BlueprintCallable)
	void SetBattleState(BattleStateEnum newBattleState);

	UFUNCTION(BlueprintCallable)
	void SetEnemyAsTargetByPosition(uint8 enemyPosition);

	UFUNCTION(BlueprintCallable)
	void SetHeroAsTargetByName(FString name);

	UFUNCTION(BlueprintCallable)
	void CastSpell(uint8 position);

	// UFUNCTION(BlueprintCallable)
	// virtual void BeginPlay() override;

	AMyGameState();
};
