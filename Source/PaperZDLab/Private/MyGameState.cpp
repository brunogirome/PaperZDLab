// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameState.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"

TArray<UHeroClass *> AMyGameState::GetPartyMembers()
{
  return this->GameInstance->Party->Members;
}

TArray<UEnemyClass *> AMyGameState::GetEnemyPartyMembers()
{
  return this->GameMode->EnemyParty;
}

TArray<float> AMyGameState::GetATTACK_STRENGTH_ACCURACY()
{
  return this->GameMode->ATTACK_STRENGTH_ACCURACY_BASE;
}

TEnumAsByte<CurrentGameState> AMyGameState::GetCurrentGameState()
{
  return this->GameInstance->CurrentGameState;
}

void AMyGameState::SetCurrentGameMode(CurrentGameState newCurrentGameState)
{
  this->GameInstance->CurrentGameState = newCurrentGameState;
}

TEnumAsByte<BattleStateEnum> AMyGameState::GetLastBattleState()
{
  return this->GameMode->LastBattleState;
}

TEnumAsByte<BattleStateEnum> AMyGameState::GetBattleState()
{
  return this->GameMode->BattleState;
}

void AMyGameState::SetBattleState(BattleStateEnum newBattleState)
{
  this->GameMode->SetBattleState(newBattleState);
}

UCombatActorClass *AMyGameState::GetCurrentActor()
{
  return this->GameMode->CurrentActor;
}

void AMyGameState::SetCurrentTarget(uint8 targetPosition, TypeOfActorEnum typeOfActor)
{
  UCombatActorClass *targetActor =
      typeOfActor == ENEMY ? (UCombatActorClass *)this->GameMode->EnemyParty[targetPosition]
                           : (UCombatActorClass *)(*this->GameMode->HeroParty)[targetPosition];

  this->GameMode->TargetActor = targetActor;
}

void AMyGameState::SetAtackStrengthChoice(uint8 choice)
{
  this->GameMode->AtackStrengthChoice = choice;

  this->GameMode->BattleState = PHYSICAL_ATTACK;
}

void AMyGameState::StartBattle(TArray<FName> enemiesRowNames)
{
  this->GameMode->StartBattle(enemiesRowNames);
}

void AMyGameState::CastSpell(uint8 position)
{
  this->GameMode->CastedSpellPositon = position;

  this->GameMode->BattleState = SPELL_CAST;
}

TEnumAsByte<SpellTypeEnum> AMyGameState::GetSpellCastedType()
{
  return this->GameMode->CastedSpell->SpellType;
}

// void AMyGameState::BeginPlay()
// {
//   Super::BeginPlay();
// }

AMyGameState::AMyGameState()
{
  this->GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  this->GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}