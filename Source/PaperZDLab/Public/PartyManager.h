// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartyManager.generated.h"

class AHero;

class APartyLeader;

class APartyMember;

class UMyGameInstance;

class AMyGameMode;

// Hero refs, spawn, add hero, remove hero, change order

/**
 *
 */
UCLASS()
class PAPERZDLAB_API UPartyManager : public UObject
{
	GENERATED_BODY()

	void spawnAIHero();

	UMyGameInstance *gameInstance;

	AMyGameMode *gameMode;

public:
	APartyLeader *Leader;

	TArray<APartyMember *> AIMembers;

	TArray<AHero *> Heroes;

	void Start(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef);

	UPartyManager();
};
