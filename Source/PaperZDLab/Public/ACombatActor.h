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
  TEnumAsByte<TypeOfActorEnum> TypeOfActor;

  virtual void BeginPlay() override;

  virtual void Tick(float DeltaTime) override;

  ACombatActor();
};
