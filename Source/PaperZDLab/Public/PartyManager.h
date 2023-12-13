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

struct FHeroStruct;

// Hero refs, spawn, add hero, remove hero, change order

/**
 *
 */
UCLASS()
class PAPERZDLAB_API UPartyManager : public UObject
{
	GENERATED_BODY()

	FHeroStruct *getHeroStruct(FName heroName);

	void spawnAIHero(FHeroStruct *heroStruct);

	UMyGameInstance *gameInstance;

	AMyGameMode *gameMode;

public:
	APartyLeader *Leader;

	TArray<APartyMember *> AIMembers;

	TArray<AHero *> Heroes;

	void Start(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef);

	void AddHero(FName name);

	UPartyManager();
};
