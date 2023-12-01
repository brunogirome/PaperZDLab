// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ACombatActor.h"

#include "TypeOfActorEnum.h"

#include "AEnemyActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AEnemyActor : public ACombatActor
{
  GENERATED_BODY()

public:
  virtual void BeginPlay() override;

  virtual void Tick(float DeltaTime) override;

  AEnemyActor();
};
