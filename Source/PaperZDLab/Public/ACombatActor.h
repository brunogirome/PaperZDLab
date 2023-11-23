// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawnnableActor.h"

#include "ACombatActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ACombatActor : public ASpawnnableActor
{
    GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime) override;

    ACombatActor();
};
