// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"

ActorAttackOrder::ActorAttackOrder(int32 position, UCombatActorClass *actorClass)
{
  this->Position = position;

  this->Speed = actorClass->Speed;

  this->IsDead = actorClass->IsDead();

  this->Name = actorClass->Name;

  this->TypeOfActor = actorClass->TypeOfActor;
}

void AMyGameMode::incrementActorPointer()
{
  this->CurrentActorPointer++;

  this->CurrentActorPointer = this->CurrentActorPointer >= this->turnSize ? 0 : this->CurrentActorPointer;
}

void AMyGameMode::startStep()
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
      this->incrementActorPointer();

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

void AMyGameMode::physicalDamage()
{
  int32 attackerDamage = this->currentActor->PhysicalDamage;

  int32 defenserDefense = this->TargetActor->PhysicalDefense;

  int32 damage = attackerDamage - (int32)(defenserDefense * 0.7);

  this->TargetActor->TakeDamage(damage);

  FString attackerName = this->currentActor->Name;

  FString defenderName = this->TargetActor->Name;

  GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, attackerName + " dealt " + FString::FromInt(damage) + " on " + defenderName + "!");

  this->incrementActorPointer();

  this->BattleState = START_STEP;
}

void AMyGameMode::BeginPlay()
{
  Super::BeginPlay();

  if (!this->GameInstance->Party)
  {
    this->GameInstance->InitParty();
  }
}

void AMyGameMode::Tick()
{
  if (this->GameInstance->CurrentGameState != BATTLE)
  {
    return;
  }

  switch (this->BattleState)
  {
  case START_STEP:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Start Step");

    this->startStep();

    break;
  case PHYSICAL_ATTACK:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Physical Attack");

    this->physicalDamage();

    break;
  default:
    break;
  }
}

void AMyGameMode::StartBattle(TArray<FName> enemyNames)
{
  this->HeroParty = &this->GameInstance->Party->Members;

  for (FName enemyRowName : enemyNames)
  {
    FEnemyStruct *enemyStructPointer = this->GameInstance->EnemiesDataTable->FindRow<FEnemyStruct>(enemyRowName, "", true);

    UEnemyClass *enemyInstance = NewObject<UEnemyClass>(UEnemyClass::StaticClass());

    enemyInstance->Init(enemyStructPointer, this->GameInstance);

    this->EnemyParty.Add(enemyInstance);
  }

  this->turnSize = this->HeroParty->Num() + this->EnemyParty.Num();

  this->BattleState = START_STEP;

  this->GameInstance->CurrentGameState = BATTLE;
}

AMyGameMode::AMyGameMode()
{
  this->GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  const uint8 DEFAULT_WEAK_ATTACK_ACCURAY = 86;

  const uint8 DEFAULT_MEDIUM_ATTACK_ACCURAY = 76;

  const uint8 DEFAULT_STRONG_ATTACK_ACCURAY = 66;

  this->ATTACK_STRENGTH_ACCURACY.Emplace(DEFAULT_WEAK_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY.Emplace(DEFAULT_MEDIUM_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY.Emplace(DEFAULT_STRONG_ATTACK_ACCURAY);
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
