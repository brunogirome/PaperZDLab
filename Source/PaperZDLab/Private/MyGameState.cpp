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

TEnumAsByte<BattleStateEnum> AMyGameState::GetBattleState()
{
  return this->GameMode->BattleState;
}

TEnumAsByte<BattleStateEnum> AMyGameState::GetLastBattleState()
{
  return this->GameMode->LastBattleState;
}

TEnumAsByte<SpellTypeEnum> AMyGameState::GetSpellCastedType()
{
  return this->GameMode->CastedSpell->SpellType;
}

UCombatActorClass *AMyGameState::GetCurrentActor()
{
  return this->GameMode->CurrentActor;
}

void AMyGameState::SetBattleState(BattleStateEnum newBattleState)
{
  this->GameMode->SetBattleState(newBattleState);
}

UHeroClass *AMyGameState::GetHeroByPartyPosition(uint8 position)
{
  return (*this->GameMode->HeroParty)[position];
}

UEnemyClass *AMyGameState::GetEnemyByPartyPosition(uint8 position)
{
  return this->GameMode->EnemyParty[position];
}

void AMyGameState::SetCurrentGameMode(CurrentGameState newCurrentGameState)
{
  this->GameInstance->CurrentGameState = newCurrentGameState;
}

void AMyGameState::SetEnemyAsTargetByPosition(uint8 enemyPosition)
{
  UCombatActorClass *enemy = (UCombatActorClass *)this->GameMode->EnemyParty[enemyPosition];

  this->GameMode->TargetActor = enemy;
}

void AMyGameState::SetHeroAsTargetByName(FString name)
{
  int32 heroIndex =
      (*this->GameMode->HeroParty).IndexOfByPredicate([&](UHeroClass *hero)
                                                      { return hero->Name == name; });

  UCombatActorClass *hero = (UCombatActorClass *)(*this->GameMode->HeroParty)[heroIndex];

  this->GameMode->TargetActor = hero;
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

// void AMyGameState::BeginPlay()
// {
//   Super::BeginPlay();
// }

AMyGameState::AMyGameState()
{
  this->GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  this->GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}