// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ACombatActor.h"

#include "AProtagonistActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AProtagonistActor : public ACombatActor
{
    GENERATED_BODY()

    class UMyGameInstance *myGameInstance;

public:
    AProtagonistActor();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class USpringArmComponent *SpringArmComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class UCameraComponent *CameraComp;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent);

    void Move(const struct FInputActionValue &Value);
};
