// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyPartyMember.generated.h"

struct FEnemyStruct;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AEnemyPartyMember : public AEnemy
{
	GENERATED_BODY()

public:
	void Initialize(FEnemyStruct *enemyStruct);

	AEnemyPartyMember();

	virtual void BeginPlay() override;
};
