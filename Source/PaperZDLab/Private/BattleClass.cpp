// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleClass.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameModeBase.h"

ActorAttackOrder::ActorAttackOrder(int32 position, UCombatActorClass *actorClass)
{
  this->Position = position;

  this->Speed = actorClass->Speed;

  this->IsDead = actorClass->IsDead();

  this->Name = actorClass->Name;

  this->TypeOfActor = actorClass->TypeOfActor;
}

void ABattleClass::Init(TArray<FName> enemyNames)
{
  AMyGameModeBase *game = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

  this->Party = &game->Party->Members;

  UDataTable *enemiesDataTable = game->EnemiesDataTable;

  for (FName enemyRowName : enemyNames)
  {
    FEnemyStruct *enemyStructPointer = enemiesDataTable->FindRow<FEnemyStruct>(enemyRowName, "", true);

    UEnemyClass *enemyInstance = NewObject<UEnemyClass>(UEnemyClass::StaticClass());

    enemyInstance->Init(enemyStructPointer);

    this->EnemyParty.Emplace(enemyInstance);
  }

  this->turnSize = this->Party->Num() + this->EnemyParty.Num();

  this->BattleState = START_STEP;
}

void ABattleClass::SortTurn()
{
  // Sorting the turn
  this->attackOrder.Empty();

  int32 index = 0;

  for (auto *hero : *this->Party)
  {
    ActorAttackOrder attackActor(index, hero);

    this->attackOrder.Emplace(attackActor);

    index++;
  }

  index = 0;

  for (auto *enemy : this->EnemyParty)
  {
    ActorAttackOrder attackActor(index, enemy);

    this->attackOrder.Emplace(attackActor);

    index++;
  }

  this->attackOrder.Sort(
      [](const ActorAttackOrder &A, const ActorAttackOrder &B)
      { return A.Speed > B.Speed; });

  // Deciding the next attacker
  bool validActor = false;

  while (!validActor)
  {
    ActorAttackOrder currentAttacker = this->attackOrder[this->CurrentActorPointer];

    if (currentAttacker.IsDead)
    {
      this->IncrementActorPointer();

      continue;
    }

    if (currentAttacker.TypeOfActor == HERO)
    {
      this->currentActor = (UCombatActorClass *)(*Party)[currentAttacker.Position];

      this->BattleState = HERO_TURN;
    }
    else
    {
      this->currentActor = (UCombatActorClass *)EnemyParty[currentAttacker.Position];

      this->BattleState = ENEMY_TURN;
    }

    validActor = true;
  }
}

void ABattleClass::IncrementActorPointer()
{
  this->CurrentActorPointer++;

  this->CurrentActorPointer = this->CurrentActorPointer >= this->turnSize ? 0 : this->CurrentActorPointer;
}

// Debug Functions
void ABattleClass::PrintSort()
{
  for (auto actor : attackOrder)
  {
    FString isDead = actor.IsDead ? "true" : "false";

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, actor.Name + TEXT(", Speed: ") + FString::FromInt(actor.Speed) + TEXT(", Position: ") + FString::FromInt(actor.Position) + TEXT(", IsDead: ") + isDead);
  }
}

void ABattleClass::PrintNames()
{
  for (auto *hero : *this->Party)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, hero->Name);
  }

  for (auto *enemy : this->EnemyParty)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, enemy->Name);
  }
}

ABattleClass::ABattleClass() {}