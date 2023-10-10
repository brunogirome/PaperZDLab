// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Engine/DataTable.h"

#include "HeroClass.h"

#include "PartyClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UPartyClass : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UHeroClass *> Members;

	UDataTable *HeroesDataTable;

	UPartyClass();

	UFUNCTION(BlueprintCallable)
	void LoadMembers();
};
