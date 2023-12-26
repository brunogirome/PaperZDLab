// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyLeader.generated.h"

class UMyGameInstance;

class APartyLeader;

class AHero;

// temporary
struct FAIRequestID;

struct FPathFollowingResult;

struct FheroesGoalLocation
{
	FVector Location;

	bool Reached;

	FheroesGoalLocation(FVector location) : Location(location)
	{
		this->Reached = false;
	}
};

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AEnemyLeader : public AEnemy
{
	GENERATED_BODY()

	APartyLeader *partyLeader;

	TArray<AHero *> *heroesPointer;

	TArray<AEnemy *> enemies;

	UMyGameInstance *localGameInstance;

	TArray<FheroesGoalLocation> heroesGoalLocation;

	bool positioning;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> EnemyNames;

	UFUNCTION(BlueprintCallable)
	void PositionHeroes();

	void SetHeroDirections();

	void SetupEnemies();

	void TempOnComplete(FAIRequestID RequestID, const FPathFollowingResult &Result);

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	AEnemyLeader();
};
