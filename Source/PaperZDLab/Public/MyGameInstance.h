// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "PartyClass.h"

#include "CurrentGameState.h"

#include "MyGameInstance.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Editanywhere, Category = "Initial Data", META = (Name = "Initial Hero Party"))
	TArray<FName> PartyRowNames;

	UPROPERTY(Editanywhere, Category = "Data Table", META = (Name = "Heroes Data Table"))
	UDataTable *HeroesDataTable;

	UPROPERTY(Editanywhere, Category = "Data Table", META = (Name = "Enemies Data Table"))
	UDataTable *EnemiesDataTable;

	UPROPERTY(Editanywhere, Category = "Data Table", META = (Name = "Spells Data Table"))
	UDataTable *SpellsDataTable;

	UPartyClass *Party;

	UMyGameInstance();

	void InitParty();

	TEnumAsByte<CurrentGameState> CurrentGameState;

	// UFUNCTION(BlueprintCallable)
	// virtual void Init() override;
};
