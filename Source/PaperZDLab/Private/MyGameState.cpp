// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameState.h"

#include "Kismet/GameplayStatics.h"

TArray<UHeroClass *> AMyGameState::GetPartyMembers()
{
  return this->GameInstance->Party->Members;
}

TArray<UEnemyClass *> AMyGameState::GetEnemyPartyMembers()
{
  return this->GameMode->EnemyParty;
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

void AMyGameState::BeginPlay()
{
  Super::BeginPlay();

  this->GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  this->GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

AMyGameState::AMyGameState() {}