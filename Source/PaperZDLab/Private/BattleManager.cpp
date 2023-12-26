// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"

#include "Navigation/PathFollowingComponent.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"

#include "PartyManager.h"

#include "EnemyLeader.h"
#include "EnemyPartyMember.h"
#include "Hero.h"

#include "EnemyStruct.h"

void UBattleManager::Intialize(TArray<FName> enemies, AEnemyLeader *enemyLeader, UMyGameInstance *myGameInstance, AMyGameMode *myGameMode)
{
  myGameInstance->CurrentGameState = BATTLE;

  this->gameInstance = myGameInstance;

  this->gameMode = myGameMode;

  this->heroParty = &this->gameInstance->PartyManager->Heroes;

  this->enemyParty.Emplace(enemyLeader);

  FVector enemyLeaderLocation = enemyLeader->GetActorLocation();

  FRotator rotation = enemyLeader->GetActorRotation();

  for (FName enemyName : enemies)
  {
    FEnemyStruct *enemyStruct = this->gameInstance->HeroesDataTable->FindRow<FEnemyStruct>(enemyName, "", true);

    if (enemyStruct)
    {
      AEnemyPartyMember *enemyMember = this->gameMode->GetWorld()->SpawnActor<AEnemyPartyMember>(AEnemyPartyMember::StaticClass(), enemyLeaderLocation, rotation);

      enemyMember->Initialize(enemyStruct);

      this->enemyParty.Emplace(enemyMember);
    }
  }

  const float DISTANCE_X = 220.f;

  const float DISTANCE_Y = 420.f;

  auto getPosition = [&](int32 position)
  {
    FVector newLocation = enemyLeaderLocation;

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

  // UPathFollowingComponent *PathFollowingCompl = GetPathFollowingComponent();

  FVector location = getPosition(0);

  for (int32 i = 1; i < (*this->heroParty).Num(); i++)
  {
    (*this->heroParty)[i]->GetController()->StopMovement();
  }

  for (int32 i = 1; i < (*this->heroParty).Num(); i++)
  {
    location = getPosition(i);

    AAIController *heroController = (*this->heroParty)[i]->ActorAIController;

    if (!heroController)
    {
      continue;
    }

    UPathFollowingComponent *followPath = heroController->GetPathFollowingComponent();

    if (!followPath)
    {
      continue;
    }

    followPath->OnRequestFinished.AddUObject(this, &UBattleManager::OnMoveComplete);

    heroController->MoveToLocation(location);
  }
}

void UBattleManager::OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
  GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Yellow, "Complete");
}

UBattleManager::UBattleManager() {}