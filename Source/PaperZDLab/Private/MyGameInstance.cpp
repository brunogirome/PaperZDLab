// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
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

void UMyGameInstance::InitParty(TArray<FName> partyRowNames)
{
  this->Party = NewObject<UPartyClass>(UPartyClass::StaticClass());

  this->Party->Init(partyRowNames);
}