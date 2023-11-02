// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::InitParty()
{
  this->Party = NewObject<UPartyClass>(UPartyClass::StaticClass());

  this->Party->Init(this);
}

void UMyGameInstance::AddItem(FName itemName, uint8 amount)
{
  for (UItemClass *item : this->Inventory)
  {
    if (item->Name == itemName)
    {
      item->AmountInInventory += amount;

      return;
    }
  }

  int32 itemPositon = this->Inventory.Num() - 1;

  FItemStruct *itemStructPointer = this->ItemsDataTable->FindRow<FItemStruct>(itemName, "", true);

  UItemClass *newItem = NewObject<UItemClass>(UItemClass::StaticClass());

  newItem->Create(itemPositon, amount, itemStructPointer, this);

  this->Inventory.Emplace(newItem);
}

void UMyGameInstance::RemoveItem(int32 positon)
{
  this->Inventory.RemoveAt(positon);
}

UMyGameInstance::UMyGameInstance()
{
  this->CurrentGameState = OVERWORLD;

  this->Party = nullptr;

  const float DEFAULT_WEAK_ATTACK_ACCURAY = 92.f;

  const float DEFAULT_MEDIUM_ATTACK_ACCURAY = 82.f;

  const float DEFAULT_STRONG_ATTACK_ACCURAY = 72.f;

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_WEAK_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_MEDIUM_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_STRONG_ATTACK_ACCURAY);
}