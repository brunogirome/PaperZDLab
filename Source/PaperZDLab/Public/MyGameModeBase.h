// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PartyClass.h"

#include "MyGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UPartyClass *Party;

	UPROPERTY(BluePrintReadWrite)
	TArray<FName> HeroesNames;

	UDataTable *HeroesDataTable;

	UDataTable *EnemiesDataTable;

	AMyGameModeBase();

	UFUNCTION(BlueprintCallable)
	void Start(TArray<FName> initialHeroes);
};
