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

void AMyGameMode::startStep()
{
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

  bool validActor = false;

  while (!validActor)
  {
    ActorAttackOrder currentAttacker = this->attackOrder[this->currentActorPointer];

    if (currentAttacker.IsDead)
    {
      this->incrementActorPointer();

      continue;
    }

    if (currentAttacker.TypeOfActor == HERO)
    {
      this->CurrentActor = (UCombatActorClass *)(*HeroParty)[currentAttacker.Position];

      this->SetBattleState(HERO_TURN);
    }
    else
    {
      this->CurrentActor = (UCombatActorClass *)EnemyParty[currentAttacker.Position];

      this->SetBattleState(ENEMY_TURN);
    }

    validActor = true;
  }

  this->alreadyAttacked = false;
}

void AMyGameMode::physicalDamage()
{
  float accuracy = this->ATTACK_STRENGTH_ACCURACY_BASE[this->AtackStrengthChoice];

  accuracy *= 1 + (this->CurrentActor->Agility / 300);

  float dieroll = FMath::FRandRange(0.f, 100.f);

  dieroll += this->TargetActor->Evasion / 2;

  FString attackerName = this->CurrentActor->Name;

  if (dieroll <= accuracy)
  {
    float bonusDamage = 1 + (this->AtackStrengthChoice * 5 / 100);

    int32 attackerDamage = this->CurrentActor->PhysicalDamage * bonusDamage;

    int32 defenserDefense = this->TargetActor->PhysicalDefense;

    int32 damage = attackerDamage - (int32)(defenserDefense * 0.7);

    FString defenderName = this->TargetActor->Name;

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, attackerName + " dealt " + FString::FromInt(damage) + " on " + defenderName + "!");

    this->TargetActor->TakeDamage(damage);
  }
  else
  {
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, attackerName + " missed!");
  }

  uint8 staminaCost = this->AtackStrengthChoice + 1;

  this->CurrentActor->ReduceStamina(staminaCost);

  this->SetBattleState(
      !this->CurrentActor->IsOutOfStamina() ? ATTACK_DECISION : END_OF_THE_TURN);
}

void AMyGameMode::castSpell()
{
  this->CastedSpell = this->CurrentActor->Spells[this->CastedSpellPositon];

  switch (CastedSpell->SpellType)
  {
  case DAMAGE:
    this->SetBattleState(SELECT_TARGET);
    break;

  default:
    break;
  }
}

void AMyGameMode::castSpellDamage()
{
  this->CurrentActor->UseMana(CastedSpell->ManaCost);

  int32 magicDamage =
      this->CurrentActor->MagicDamage + this->CastedSpell->Amount;

  int32 targetDefense = this->TargetActor->MagicDamage;

  int32 damage = magicDamage - targetDefense;

  FString attackerName = this->CurrentActor->Name;

  FString defenderName = this->TargetActor->Name;

  GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, attackerName + " dealt " + FString::FromInt(damage) + " on " + defenderName + "!");

  this->TargetActor->TakeDamage(damage);

  this->CurrentActor->ReduceStamina((int32)(CurrentActor->Stamina / 66.66f));

  this->SetBattleState(END_OF_THE_TURN);
}

void AMyGameMode::endOfTheTurn()
{
  bool endOfTurnCycle = this->turnCurrent % this->turnSize == 0;

  this->victory = true;

  this->gameOver = true;

  for (auto *hero : *this->HeroParty)
  {
    if (!hero->IsDead())
    {
      this->gameOver = false;
    }

    if (endOfTurnCycle)
    {
      hero->HealStamina(hero->Stamina);
    }
  }

  for (auto *enemy : this->EnemyParty)
  {
    if (!enemy->IsDead())
    {
      this->victory = false;
    }

    if (endOfTurnCycle)
    {
      enemy->HealStamina(enemy->Stamina);
    }
  }

  this->incrementActorPointer();

  this->SetBattleState(!(victory || gameOver) ? START_STEP : END_OF_THE_BATTLE);
}

void AMyGameMode::incrementActorPointer()
{
  this->currentActorPointer++;

  this->currentActorPointer = this->currentActorPointer >= this->turnSize ? 0 : this->currentActorPointer;
}

void AMyGameMode::BeginPlay()
{
  Super::BeginPlay();

  if (!this->gameInstance->Party)
  {
    this->gameInstance->InitParty();
  }
}

void AMyGameMode::Tick(float DeltaSeconds)
{
  if (this->gameInstance->CurrentGameState != BATTLE)
  {
    return;
  }

  switch (this->BattleState)
  {
  case START_STEP:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Start step");

    this->startStep();

    break;
  case PHYSICAL_ATTACK:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Physical attack");

    this->physicalDamage();

    break;
  case SPELL_CAST:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Spell cast");

    this->castSpell();

    break;
  case SPELL_DAMAGE_CAST:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Spell damage cast");

    this->castSpellDamage();

    break;
  case END_OF_THE_TURN:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "End of the turn");

    this->endOfTheTurn();

    break;
  case END_OF_THE_BATTLE:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "End of the battle");

    this->gameInstance->CurrentGameState = OVERWORLD;

    break;
  default:
    break;
  }
}

void AMyGameMode::StartBattle(TArray<FName> enemyNames)
{
  this->HeroParty = &this->gameInstance->Party->Members;

  uint8 index = 0;

  for (FName enemyRowName : enemyNames)
  {
    FEnemyStruct *enemyStructPointer = this->gameInstance->EnemiesDataTable->FindRow<FEnemyStruct>(enemyRowName, "", true);

    UEnemyClass *enemyInstance = NewObject<UEnemyClass>(UEnemyClass::StaticClass());

    enemyInstance->Init(enemyStructPointer, this->gameInstance, index);

    this->EnemyParty.Add(enemyInstance);

    index++;
  }

  this->turnCurrent = 1;

  this->turnSize = this->HeroParty->Num() + this->EnemyParty.Num();

  this->BattleState = START_STEP;

  this->gameInstance->CurrentGameState = BATTLE;
}

void AMyGameMode::SetBattleState(BattleStateEnum newState)
{
  this->LastBattleState = this->BattleState;

  this->BattleState = newState;
}

AMyGameMode::AMyGameMode()
{
  this->gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  const float DEFAULT_WEAK_ATTACK_ACCURAY = 92.f;

  const float DEFAULT_MEDIUM_ATTACK_ACCURAY = 82.f;

  const float DEFAULT_STRONG_ATTACK_ACCURAY = 72.f;

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_WEAK_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_MEDIUM_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_STRONG_ATTACK_ACCURAY);

  this->currentActorPointer = 0;

  this->alreadyAttacked = false;

  this->victory = false;

  this->gameOver = false;
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
