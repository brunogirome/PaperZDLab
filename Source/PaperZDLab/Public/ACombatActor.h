// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawnnableActor.h"

#include "TypeOfActorEnum.h"

#include "AIController.h"

#include "ACombatActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ACombatActor : public ASpawnnableActor
{
    GENERATED_BODY()

    AAIController *aIController;

    bool alreadyPossessed;

public:
    APawn *TargetPawn;

    FName HeroName;

    bool IsLeader = false;

    UPROPERTY(BlueprintReadOnly)
    TEnumAsByte<TypeOfActorEnum> TypeOfActor;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    void FollowActor();

    ACombatActor();
};
