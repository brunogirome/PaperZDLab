// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawnnableActor.h"

#include "TypeOfActorEnum.h"

#include "APartyMember.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API APartyMember : public ACombatActor
{
    GENERATED_BODY()

public:
    APawn *TargetPawn;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    APartyMember();
};
