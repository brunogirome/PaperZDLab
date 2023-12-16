// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyLeader.generated.h"

class UMyGameInstance;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AEnemyLeader : public AEnemy
{
	GENERATED_BODY()

	UMyGameInstance *localGameInstance;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> EnemyNames;

	UFUNCTION(BlueprintCallable)
	void PositionHeroes();

	virtual void BeginPlay() override;

	AEnemyLeader();
};
