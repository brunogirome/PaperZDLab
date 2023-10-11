// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleClass.h"

ActorAttackOrder::ActorAttackOrder(int32 position, UCombatActorClass *actorClass)
{
  this->Position = position;

  this->Speed = actorClass->Speed;

  this->IsDead = actorClass->IsDead();

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

ABattleClass::ABattleClass()
{
  static ConstructorHelpers::FObjectFinder<UDataTable>
      Enemies_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Enemies_DataTable.Enemies_DataTable'"));

  EnemiesDataTable = Enemies_DataTable_Ref.Object;
}