// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawnnableActor.h"

#include "TypeOfActorEnum.h"

#include "ACombatActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ACombatActor : public ASpawnnableActor
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    TEnumAsByte<TypeOfActorEnum> TypeOfActor;

    virtual void Tick(float DeltaTime) override;

    ACombatActor();
};
