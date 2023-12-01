// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ACombatActor.h"

#include "TypeOfActorEnum.h"

#include "APartyMemberActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API APartyMemberActor : public ACombatActor
{
    GENERATED_BODY()

public:
    APawn *TargetPawn;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    APartyMemberActor();
};
