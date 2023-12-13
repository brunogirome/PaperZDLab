// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyLeader.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AEnemyLeader : public AEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> EnemyNames;
};
