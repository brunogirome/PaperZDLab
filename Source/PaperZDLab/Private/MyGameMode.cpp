// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"

AMyGameMode::AMyGameMode()
{
  static ConstructorHelpers::FObjectFinder<UDataTable>
      Enemies_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Enemies_DataTable.Enemies_DataTable'"));

  this->EnemiesDataTable = Enemies_DataTable_Ref.Object;
}

ActorAttackOrder::ActorAttackOrder(int32 position, UCombatActorClass *actorClass)
{
  this->Position = position;

  this->Speed = actorClass->Speed;

  this->IsDead = actorClass->IsDead();

  this->Name = actorClass->Name;

  this->TypeOfActor = actorClass->TypeOfActor;
}

void AMyGameMode::IncrementActorPointer()
{
  this->CurrentActorPointer++;

  this->CurrentActorPointer = this->CurrentActorPointer >= this->turnSize ? 0 : this->CurrentActorPointer;
}

void AMyGameMode::StartBattle(TArray<FName> enemyNames)
{
  UMyGameInstance *gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  this->HeroParty = &(gameInstance->Party->Members);

  for (FName enemyRowName : enemyNames)
  {
    FEnemyStruct *enemyStructPointer = this->EnemiesDataTable->FindRow<FEnemyStruct>(enemyRowName, "", true);

    UEnemyClass *enemyInstance = NewObject<UEnemyClass>(UEnemyClass::StaticClass());

    enemyInstance->Init(enemyStructPointer);

    this->EnemyParty.Emplace(enemyInstance);
  }

  this->turnSize = this->HeroParty->Num() + this->EnemyParty.Num();

  this->BattleState = START_STEP;
}

void AMyGameMode::SortTurn()
{
  // Sorting the turn
  this->attackOrder.Empty();

  int32 index = 0;

  for (auto *hero : *this->HeroParty)
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
      this->currentActor = (UCombatActorClass *)(*HeroParty)[currentAttacker.Position];

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

// Debug Functions
void AMyGameMode::PrintSort()
{
  for (auto actor : attackOrder)
  {
    FString isDead = actor.IsDead ? "true" : "false";

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, actor.Name + TEXT(", Speed: ") + FString::FromInt(actor.Speed) + TEXT(", Position: ") + FString::FromInt(actor.Position) + TEXT(", IsDead: ") + isDead);
  }
}

void AMyGameMode::PrintNames()
{
  for (auto *hero : *this->HeroParty)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, hero->Name);
  }

  for (auto *enemy : this->EnemyParty)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, enemy->Name);
  }
}
