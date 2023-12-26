// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hero.h"

#include "PartyLeader.generated.h"

class USpringArmComponent;

class UCameraComponent;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API APartyLeader : public AHero
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USpringArmComponent *SpringArmComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UCameraComponent *CameraComp;

    void SetupControllerForBattle();

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent);

    void Move(const struct FInputActionValue &Value);

    APartyLeader();
};
