// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hero.h"

#include "TypeOfActorEnum.h"

#include "PartyMember.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API APartyMember : public AHero
{
    GENERATED_BODY()

public:
    APawn *TargetPawn;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    APartyMember();
};
