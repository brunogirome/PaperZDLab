// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"

float AMyGameMode::getDefendingDamageReduction()
{
  return this->TargetActor->IsDefending ? this->DEFENDING_DAMAGE_REDUCTION : 1;
}

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

  this->CurrentActor->IsDefending = false;
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

    int32 damage = (attackerDamage - (int32)(defenserDefense * 0.7)) * this->getDefendingDamageReduction();

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

  if (this->CastedSpell->SpellType != PARTY_BUFF)
  {
    this->SetBattleState(SELECT_TARGET);
  }
  else
  {
    this->SetBattleState(SPELL_DAMAGE_CAST);
  }
}

void AMyGameMode::castItem()
{
  FString actorName = this->CurrentActor->Name;

  FString targetName = this->TargetActor->Name;

  FString itemName = this->SelectedItem->Name;

  switch (this->SelectedItem->ConsumableType)
  {
  case POTION_HP:
    this->TargetActor->HealHp(this->SelectedItem->ConsumableHealing);

    GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Yellow, actorName + " used " + itemName + " on " + targetName + "!");

    this->SelectedItem->Consume();
    break;
  case POTION_MANA:
    break;
  default:
    break;
  }

  this->CurrentActor->ReduceStamina((int32)(CurrentActor->Stamina / 66.66f));

  this->SetBattleState(END_OF_THE_TURN);
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

  UEnemyClass *enemy = this->EnemyParty[this->CurrentActor->PositionForEnemyInBattle];

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

  FString defenderName;

  bool buffAlreadyActive = false;

  switch (this->CastedSpell->SpellType)
  {
  case DAMAGE:
  {
    int32 magicDamage =
        this->CurrentActor->MagicDamage + this->CastedSpell->Amount;

    int32 targetDefense = this->TargetActor->MagicDamage;

    int32 spellDamage = (magicDamage - targetDefense) * this->getDefendingDamageReduction();

    defenderName = this->TargetActor->Name;

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, attackerName + " dealt " + FString::FromInt(spellDamage) + " on " + defenderName + "!");

    this->TargetActor->TakeDamage(spellDamage);
    break;
  }
  case BUFF:
  {
    for (FActiveBuffStruct &targetActiveBuff : this->TargetActor->ActiveBuffs)
    {
      FActiveBuffStruct *activeBuffPointer = &targetActiveBuff;

      defenderName = this->TargetActor->Name;

      GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, attackerName + " casted " + this->CastedSpell->Name + " on " + defenderName + "!");

      if (activeBuffPointer->SpellPointer->BuffType == this->CastedSpell->BuffType)
      {
        buffAlreadyActive = true;

        activeBuffPointer->IncreaseRounds(this->CastedSpell->GetRoundsForCasting());

        if (this->CastedSpell->Multiplier > activeBuffPointer->SpellPointer->Multiplier)
        {
          activeBuffPointer->SpellPointer->Multiplier = this->CastedSpell->Multiplier;
        }

        break;
      }
    }

    if (!buffAlreadyActive)
    {
      this->TargetActor->AddBuff(this->CastedSpell);
    }

    break;
  }
  case HEALING:
  {
    int32 healedAmount = this->CastedSpell->Amount;

    defenderName = this->TargetActor->Name;

    this->TargetActor->HealHp(healedAmount);

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, attackerName + " casted " + this->CastedSpell->Name + " and healed " + FString::FromInt(healedAmount) + " for " + defenderName + "!");

    break;
  }

  case PARTY_BUFF:
  {
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::White, attackerName + " casted the party buff " + this->CastedSpell->Name + "! ");

    for (FActiveBuffStruct &buff : this->ActivePartyBuffs)
    {
      FActiveBuffStruct *activeBuffPointer = &buff;

      if (activeBuffPointer->SpellPointer->PartyBuffType == this->CastedSpell->PartyBuffType)
      {
        activeBuffPointer->RemainingRounds = this->CastedSpell->GetRoundsForCasting();

        buffAlreadyActive = true;

        break;
      }
    }

    if (!buffAlreadyActive)
    {
      this->ActivePartyBuffs.Emplace(FActiveBuffStruct(this->CastedSpell));
    }

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
    else if (actor->IsDead() && actor->IsDefending)
    {
      actor->IsDefending = false;
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
        FActiveBuffStruct *buff = &actor->ActiveBuffs[i];

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

  for (int i = 0; i < this->ActivePartyBuffs.Num(); i++)
  {
    FActiveBuffStruct *partyBuff = &this->ActivePartyBuffs[i];

    partyBuff->DecreaseRounds();

    if (partyBuff->IsBuffExpired())
    {
      this->ActivePartyBuffs.RemoveAt(i);

      i--;
    }
  }

  this->CurrentActor->IsDefending = false;

  this->turnCurrent++;

  this->incrementActorPointer();

  this->SetBattleState(!(victory || gameOver) ? START_STEP : END_OF_THE_BATTLE);
}

void AMyGameMode::tryToEscape()
{
  float escapeDieRoll = FMath::FRandRange(0.f, 1.f);

  if (escapeDieRoll < ESCAPE_CHANCE)
  {
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Turquoise, "You escaped the battle!");

    this->SetBattleState(END_OF_THE_BATTLE);
  }
  else
  {
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Turquoise, "You failed to escape!");

    this->SetBattleState(END_OF_THE_TURN);
  }
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

  this->gameInstance->AddItem("HpPotion", 5);

  this->gameInstance->AddItem("OgreAxe", 3);

  this->gameInstance->AddItem("SimpleDagger", 1);
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
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Spell Cast");

    this->castSpell();

    break;
  case SPELL_DAMAGE_CAST:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Spell Damage cast");

    this->castSpellDamage();

    break;
  case ITEM_CAST:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Item Cast");

    this->castItem();

    break;
  case DEFENDING:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Defending");

    this->SetBattleState(END_OF_THE_TURN);

    break;
  case END_OF_THE_TURN:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "End of the turn");

    this->endOfTheTurn();

    break;
  case TRYING_TO_ESCAPE:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Trying to escape");

    this->tryToEscape();

    break;
  case END_OF_THE_BATTLE:
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "End of the battle");

    this->gameInstance->CurrentGameState = OVERWORLD;

    for (UHeroClass *hero : *this->HeroParty)
    {
      hero->ActiveBuffs.Empty();
    }

    this->ActivePartyBuffs.Empty();

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

  for (uint8 i = 0; i < enemyNames.Num(); i++)
  {
    FName enemyRowName = enemyNames[i];

    FEnemyStruct *enemyStructPointer = this->gameInstance->EnemiesDataTable->FindRow<FEnemyStruct>(enemyRowName, "", true);

    UEnemyClass *enemyInstance = NewObject<UEnemyClass>(UEnemyClass::StaticClass());

    enemyInstance->Init(enemyStructPointer, this->gameInstance, i);

    this->EnemyParty.Add(enemyInstance);
  }

  for (UHeroClass *hero : *this->HeroParty)
  {
    this->attackOrder.Emplace(hero);
  }

  for (UEnemyClass *enemy : this->EnemyParty)
  {
    this->attackOrder.Emplace(enemy);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, enemy->Name);

    for (TArray<AttackPatern> moveset : enemy->Movesets)
    {
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, "New moveset");

      for (AttackPatern move : moveset)
      {
        switch (move.MoveType)
        {
        case WEAK_ATTACK:
          GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, "Weak Attack");
          break;
        case MEDIUM_ATTACK:
          GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, "Medium Attack");
          break;
        case HEAVY_ATTACK:
          GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, "Heavy Attack");
          break;
        case CAST_SPELL_MOVESET:
          GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, "Spell : " + FString::FromInt(move.SpellPosition));
          break;
        }
      }
    }
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

  this->escaped = false;
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
