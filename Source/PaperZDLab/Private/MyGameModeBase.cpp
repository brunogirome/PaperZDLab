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
}

void AMyGameModeBase::Start(TArray<FName> initialHeroes)
{
  this->HeroesNames = initialHeroes;

  this->Party = NewObject<UPartyClass>(UPartyClass::StaticClass());
}
