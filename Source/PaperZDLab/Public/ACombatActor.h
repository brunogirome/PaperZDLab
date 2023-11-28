// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawnnableActor.h"

#include "TypeOfActorEnum.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "ACombatActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ACombatActor : public ASpawnnableActor
{
    GENERATED_BODY()

    class AAIController *actorAIController;

    class AIMoveToTargetDelegate *completeDelegate;

public:
    void AIMoveToTarget();

    void Amongus2SoonTm();

    APawn *TargetPawn;

    UPROPERTY(BlueprintReadOnly)
    TEnumAsByte<TypeOfActorEnum> TypeOfActor;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    ACombatActor();
};
