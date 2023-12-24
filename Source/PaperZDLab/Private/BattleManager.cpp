// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"

#include "Hero.h"

void UBattleManager::Intialize(TArray<FName> enemies, UMyGameState myGameStateRef, FVector enemyLocation)
{
  this->gameState = myGameStateRef;

  // this->localGameInstance->CurrentGameState = BATTLE;

  this->heroesGoalLocation.Empty();

  const float DISTANCE_X = 220.f;

  const float DISTANCE_Y = 420.f;

  auto getPosition = [&](int32 position)
  {
    FVector newLocation = enemyLocation;

    newLocation.Y += DISTANCE_Y;

    switch (position)
    {
    case 0:
      newLocation.X -= DISTANCE_X * 1.5f;

      break;
    case 1:
      newLocation.X -= DISTANCE_X * 0.5f;

      newLocation.Y += 120.f;

      break;
    case 2:
      newLocation.X += DISTANCE_X * 0.5f;

      newLocation.Y += 120.f;

      break;
    case 3:
      newLocation.X += DISTANCE_X * 1.5f;

      break;
    default:
      break;
    }

    return newLocation;
  };

  for (FName enemyName : enemies)
  {
  }
}

UBattleManager::UBattleManager() {}