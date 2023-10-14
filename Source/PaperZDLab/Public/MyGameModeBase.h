// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PartyClass.h"

#include "GameStateEnum.h"

#include "MyGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UPartyClass *Party;

	UPROPERTY(BluePrintReadWrite)
	TArray<FName> HeroesRowNames;

	UPROPERTY(BluePrintReadWrite)
	TEnumAsByte<GameStateEnum> CurrentGameState = OVERWORLD;

	UDataTable *HeroesDataTable;

	UDataTable *EnemiesDataTable;

	UFUNCTION(BlueprintCallable)
	void Start(TArray<FName> initialHeroes);

	AMyGameModeBase();

	// Debug function
	UFUNCTION(BlueprintCallable)
	void PrintGameState();
};
