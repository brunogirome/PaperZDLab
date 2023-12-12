// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SpawnnableActor.h"
#include "CombatActor.h"

#include "Enemy.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AEnemy : public ASpawnnableActor, public ICombatActor
{
	GENERATED_BODY()
};
