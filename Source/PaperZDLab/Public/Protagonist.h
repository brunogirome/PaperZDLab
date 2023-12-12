// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hero.h"

#include "Protagonist.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AProtagonist : public AHero
{
    GENERATED_BODY()

    class UMyGameInstance *myGameInstance;

public:
    AProtagonist();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class USpringArmComponent *SpringArmComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class UCameraComponent *CameraComp;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent);

    void Move(const struct FInputActionValue &Value);
};
