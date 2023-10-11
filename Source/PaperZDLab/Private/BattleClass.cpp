// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleClass.h"

ActorAttackOrder::ActorAttackOrder(int32 position, UCombatActorClass *actorClass)
{
  this->Position = position;

  this->Speed = actorClass->Speed;

  this->IsDead = actorClass->IsDead();

  this->Name = actorClass->CombatActorStructPointer->Name;

  this->TypeOfActor = actorClass->CombatActorStructPointer->TypeOfActor;
}

TArray<UHeroClass *> ABattleClass::GetParty()
{
  return *this->Party;
}

void ABattleClass::Init(UPartyClass *GameParty, TArray<FName> enemiesRowNames)
{
  this->Party = &GameParty->Members;

  for (FName enemyRowName : enemiesRowNames)
  {

    FEnemyStruct *enemyStructPointer = this->EnemiesDataTable->FindRow<FEnemyStruct>(enemyRowName, "", true);

    UEnemyClass *enemyInstance = NewObject<UEnemyClass>(UEnemyClass::StaticClass());

    enemyInstance->Init(enemyStructPointer);

    this->EnemyParty.Emplace(enemyInstance);
  }

  this->turnSize = this->Party->Num() + this->EnemyParty.Num();
}

void ABattleClass::PrintNames()
{
  for (auto *hero : *this->Party)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, hero->HeroStruct.Name);
  }

  for (auto *enemy : this->EnemyParty)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, enemy->EnemyStruct->Name);
  }
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
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, TEXT("CurrentActorPointer: ") + FString::FromInt(this->CurrentActorPointer));

    ActorAttackOrder currentAttacker = this->attackOrder[this->CurrentActorPointer];

    if (currentAttacker.IsDead)
    {
      this->IncrementActorPointer();

      continue;
    }

    this->currentActor =
        currentAttacker.TypeOfActor == HERO
            ? (UCombatActorClass *)(*Party)[currentAttacker.Position]
            : (UCombatActorClass *)EnemyParty[currentAttacker.Position];

    validActor = true;
  }

  GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::White, TEXT("The first attacker is: ") + currentActor->CombatActorStructPointer->Name);
}

void ABattleClass::IncrementActorPointer()
{
  this->CurrentActorPointer++;

  this->CurrentActorPointer = this->CurrentActorPointer >= this->turnSize ? 0 : this->CurrentActorPointer;
}

void ABattleClass::PrintSort()
{

  for (auto actor : attackOrder)
  {
    FString isDead = actor.IsDead ? "true" : "false";

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, actor.Name + TEXT(", Speed: ") + FString::FromInt(actor.Speed) + TEXT(", Position: ") + FString::FromInt(actor.Position) + TEXT(", IsDead: ") + isDead);
  }

  GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, TEXT("TurnSize: ") + FString::FromInt(turnSize));
}

ABattleClass::ABattleClass()
{
  static ConstructorHelpers::FObjectFinder<UDataTable>
      Enemies_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Enemies_DataTable.Enemies_DataTable'"));

  EnemiesDataTable = Enemies_DataTable_Ref.Object;
}