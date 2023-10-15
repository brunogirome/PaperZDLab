// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"

AMyGameModeBase::AMyGameModeBase()
{
  static ConstructorHelpers::FObjectFinder<UDataTable>
      Heroes_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Heroes_DataTable.Heroes_DataTable'"));

  this->HeroesDataTable = Heroes_DataTable_Ref.Object;

  static ConstructorHelpers::FObjectFinder<UDataTable>
      Enemies_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Enemies_DataTable.Enemies_DataTable'"));

  this->EnemiesDataTable = Enemies_DataTable_Ref.Object;

  static ConstructorHelpers::FObjectFinder<UDataTable>
      Spells_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Spells_DataTable.Spells_DataTable'"));

  this->SpellsDataTable = Spells_DataTable_Ref.Object;
}

void AMyGameModeBase::Start(TArray<FName> initialHeroes)
{
  this->HeroesRowNames = initialHeroes;

  this->Party = NewObject<UPartyClass>(UPartyClass::StaticClass());

  this->Party->Init(this->HeroesRowNames, this->HeroesDataTable, this->SpellsDataTable);
}

void AMyGameModeBase::PrintGameState()
{
  FString state;

  switch (this->CurrentGameState)
  {
  case OVERWORLD:
    state = TEXT("Overworld");
    break;
  case BATTLE:
    state = TEXT("Battle");
    break;
  case MENU:
    state = TEXT("Menu");
    break;
  case PAUSE:
    state = TEXT("Pause");
    break;
  }

  GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, TEXT("Current GameState: ") + state);
}
