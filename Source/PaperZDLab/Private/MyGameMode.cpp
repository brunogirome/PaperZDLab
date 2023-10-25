// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"

void AMyGameMode::startStep()
{
  this->attackOrder.Sort(
      [](const UCombatActorClass &A, const UCombatActorClass &B)
      {
        if (A.Speed != B.Speed)
        {
          return A.Speed > B.Speed;
        }
        else
        {
          return A.TypeOfActor == HERO;
        }
      });

  bool validActor = false;

  while (!validActor)
  {
    UCombatActorClass *currentAttacker = this->attackOrder[this->currentActorPointer];

    if (currentAttacker->IsDead())
    {
      this->incrementActorPointer();

      continue;
    }

    this->CurrentActor = currentAttacker;

    this->SetBattleState(this->CurrentActor->TypeOfActor == HERO ? HERO_TURN : ENEMY_TURN);

    validActor = true;
  }

  this->alreadyAttacked = false;
}

void AMyGameMode::physicalDamage()
{
  float accuracy = this->GetActorAccuracyByStrength(this->AttackStrengthChoice);

  float dieRoll = FMath::FRandRange(0.f, 100.f);

  dieRoll += this->TargetActor->Evasion / 2;

  FString attackerName = this->CurrentActor->Name;

  if (dieRoll <= accuracy)
  {
    float bonusDamage = 1 + (this->AttackStrengthChoice * 5 / 100);

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

  uint8 staminaCost = this->AttackStrengthChoice + 1;

  this->CurrentActor->ReduceStamina(staminaCost);

  if (!this->AlreadyAttacked && this->CurrentActor->TypeOfActor == HERO)
  {
    this->AlreadyAttacked = true;
  }

  if (this->TargetActor->IsDead() || this->CurrentActor->IsOutOfStamina())
  {
    this->SetBattleState(END_OF_THE_TURN);

    return;
  }

  this->SetBattleState(ATTACK_DECISION);
}

void AMyGameMode::castSpell()
{
  this->CastedSpell = this->CurrentActor->Spells[this->CastedSpellPositon];

  switch (this->CastedSpell->SpellType)
  {
  case DAMAGE:
  {
    this->SetBattleState(SELECT_TARGET);
    break;
  }
  case BUFF:
  {
    this->SetBattleState(SELECT_TARGET);
    break;
  }
  case HEALING:
  {
    this->SetBattleState(SELECT_TARGET);
    break;
  }
  case PARTY_BUFF:
  {
    this->SetBattleState(SPELL_DAMAGE_CAST);
    break;
  }
  default:
    break;
  }
}

void AMyGameMode::enemyTurn()
{
  auto getTarget = [&]()
  {
    uint8 choice = (uint8)FMath::FRandRange(0.f, (float)this->HeroParty->Num() - 1);

    return (*this->HeroParty)[choice];
  };

  this->TargetActor = getTarget();

  while (true)
  {
    if (!this->TargetActor->IsDead())
    {
      break;
    }

    this->TargetActor = getTarget();
  }

  for (uint8 attackStrenght = 0; attackStrenght < 3; attackStrenght++)
  {
    this->AttackStrengthChoice = attackStrenght;

    this->physicalDamage();
  }
}

void AMyGameMode::castSpellDamage()
{
  this->CurrentActor->UseMana(this->CastedSpell->ManaCost);

  FString attackerName = this->CurrentActor->Name;

  FString defenderName = this->TargetActor->Name;

  switch (this->CastedSpell->SpellType)
  {
  case DAMAGE:
  {
    int32 magicDamage =
        this->CurrentActor->MagicDamage + this->CastedSpell->Amount;

    int32 targetDefense = this->TargetActor->MagicDamage;

    int32 spellDamage = magicDamage - targetDefense;

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, attackerName + " dealt " + FString::FromInt(spellDamage) + " on " + defenderName + "!");

    this->TargetActor->TakeDamage(spellDamage);
    break;
  }
  case BUFF:
  {
    bool alreadyBuffed = false;

    for (USpellClass *targetBuff : this->TargetActor->ActiveBuffs)
    {
      if (targetBuff->BuffType == this->CastedSpell->BuffType)
      {
        alreadyBuffed = true;

        targetBuff->IncreaseRounds(this->CastedSpell->GetRoundsForCasting());

        if (this->CastedSpell->Multiplier > targetBuff->Multiplier)
        {
          targetBuff->Multiplier = this->CastedSpell->Multiplier;
        }

        break;
      }
    }

    if (alreadyBuffed)
    {
      break;
    }

    this->CastedSpell->ResetRounds();

    this->TargetActor->ActiveBuffs.Emplace(this->CastedSpell);

    break;
  }
  case HEALING:
  {
    break;
  }

  case PARTY_BUFF:
  {
    break;
  }
  default:
    break;
  }

  this->CurrentActor->ReduceStamina((int32)(CurrentActor->Stamina / 33.33f));

  this->SetBattleState(END_OF_THE_TURN);
}

void AMyGameMode::endOfTheTurn()
{
  this->AlreadyAttacked = false;

  uint8 currentTurnSize = 0;

  for (UCombatActorClass *actor : this->attackOrder)
  {
    if (!actor->IsDead())
    {
      currentTurnSize++;
    }
  }

  float staminaRecoveryReduction = 1;

  if (currentTurnSize != this->turnSize)
  {
    staminaRecoveryReduction = currentTurnSize / this->turnSize;
  }

  bool endOfTurnCycle = this->turnCurrent % currentTurnSize == 0;

  this->victory = true;

  this->gameOver = true;

  for (UCombatActorClass *actor : this->attackOrder)
  {
    if (actor->TypeOfActor == ENEMY)
    {
      this->victory = victory && actor->IsDead();
    }

    if (actor->TypeOfActor == HERO)
    {
      this->gameOver = gameOver && actor->IsDead();
    }

    if (!actor->IsDead())
    {
      for (int i = 0; i < actor->ActiveBuffs.Num(); i++)
      {
        USpellClass *buff = actor->ActiveBuffs[i];

        buff->DecreaseRounds();

        if (buff->IsBuffExpired())
        {
          actor->ActiveBuffs.RemoveAt(i);

          i--;
        }
      }

      actor->CalculateStats();

      if (endOfTurnCycle)
      {
        actor->HealStamina((uint8)(actor->Stamina * staminaRecoveryReduction));
      }
    }
    else if (actor->IsDead() && actor->ActiveBuffs.Num() > 0)
    {
      actor->ActiveBuffs.Empty();
    }
  }

  this->turnCurrent++;

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
  Super::Tick(DeltaSeconds);

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
  case ENEMY_TURN:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Enemy Turn");

    this->enemyTurn();
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

    this->attackOrder.Empty();

    this->EnemyParty.Empty();

    break;
  default:
    break;
  }
}

float AMyGameMode::GetActorAccuracyByStrength(uint8 level)
{
  switch (level)
  {
  case 0:
    return this->CurrentActor->WeakAccuracy;

    break;
  case 1:
    return this->CurrentActor->MediumAccuracy;

    break;
  case 2:
    return this->CurrentActor->StrongAccuracy;

    break;
  }

  return 0;
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

  for (UHeroClass *hero : *this->HeroParty)
  {
    this->attackOrder.Emplace(hero);
  }

  for (UEnemyClass *enemy : this->EnemyParty)
  {
    this->attackOrder.Emplace(enemy);
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

  this->AlreadyAttacked = false;

  this->currentActorPointer = 0;

  this->alreadyAttacked = false;

  this->victory = false;

  this->gameOver = false;
}

// Debug Functions
void AMyGameMode::PrintSort()
{
  for (UCombatActorClass *actor : attackOrder)
  {
    FString isDead = actor->IsDead() ? "true" : "false";

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, actor->Name + TEXT(", Speed: ") + FString::FromInt(actor->Speed) + TEXT(", IsDead: ") + isDead);
  }
}

void AMyGameMode::PrintNames()
{
  for (UHeroClass *hero : *this->HeroParty)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, hero->Name);
  }

  for (UEnemyClass *enemy : this->EnemyParty)
  {
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, enemy->Name);
  }
}
