// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawnnableActor.h"

#include "AHeroActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AHeroActor : public ASpawnnableActor
{
    GENERATED_BODY()

public:
    AHeroActor();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class USpringArmComponent *SpringArmComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class UCameraComponent *CameraComp;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent);

    void Move(const FInputActionValue &Value);
};
