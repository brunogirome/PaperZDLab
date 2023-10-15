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
	UPartyClass *Party;

	UMyGameInstance();

	TEnumAsByte<CurrentGameState> CurrentGameState = OVERWORLD;

	UFUNCTION(BlueprintCallable)
	void InitParty(TArray<FName> partyNames);
};
