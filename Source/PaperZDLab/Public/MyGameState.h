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
	TEnumAsByte<CurrentGameState> GetCurrentGameState();

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<BattleStateEnum> GetBattleState();

	AMyGameState();
};
