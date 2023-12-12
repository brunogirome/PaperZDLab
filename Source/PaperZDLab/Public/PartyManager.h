// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartyManager.generated.h"

class AProtagonistActor;

class APartyMemberActor;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API UPartyManager : public UObject
{
	GENERATED_BODY()

public:
	AProtagonistActor *AProtagonist;

	TArray<APartyMemberActor *> APartyMembers;

	UPartyManager();

	void Start();
};
