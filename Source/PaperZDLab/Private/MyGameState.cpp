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

TArray<uint8> AMyGameState::GetATTACK_STRENGTH_ACCURACY()
{
  return this->GameMode->ATTACK_STRENGTH_ACCURACY;
}

TEnumAsByte<CurrentGameState> AMyGameState::GetCurrentGameState()
{
  return this->GameInstance->CurrentGameState;
}

void AMyGameState::SetCurrentGameMode(CurrentGameState newCurrentGameState)
{
  this->GameInstance->CurrentGameState = newCurrentGameState;
}

TEnumAsByte<BattleStateEnum> AMyGameState::GetBattleState()
{
  return this->GameMode->BattleState;
}

void AMyGameState::SetBattleState(BattleStateEnum newBattleState)
{
  this->GameMode->LastBattleState = this->GameMode->BattleState;

  this->GameMode->BattleState = newBattleState;
}

void AMyGameState::SetCurrentTarget(uint8 targetPosition, TypeOfActorEnum typeOfActor)
{
  UCombatActorClass *targetActor =
      typeOfActor == ENEMY ? (UCombatActorClass *)this->GameMode->EnemyParty[targetPosition]
                           : (UCombatActorClass *)(*this->GameMode->HeroParty)[targetPosition];

  this->GameMode->TargetActor = targetActor;
}

void AMyGameState::StartBattle(TArray<FName> enemiesRowNames)
{
  this->GameMode->StartBattle(enemiesRowNames);
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