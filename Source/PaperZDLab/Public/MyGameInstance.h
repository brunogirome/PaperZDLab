// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "PartyClass.h"
#include "ItemClass.h"

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

	UPROPERTY(Editanywhere, Category = "Data Table", META = (Name = "Items Data Table"))
	UDataTable *ItemsDataTable;

	TArray<UItemClass *> Inventory;

	TArray<float> ATTACK_STRENGTH_ACCURACY_BASE;

	UPartyClass *Party;

	UMyGameInstance();

	void AddItem(FName itemName, uint8 amount);

	void RemoveItem(int32 positon);

	void InitParty();

	TEnumAsByte<CurrentGameState> CurrentGameState;
};
