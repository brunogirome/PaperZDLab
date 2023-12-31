// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

#include "ItemClass.h"
#include "PartyManager.h"
#include "MyGameMode.h"

void UMyGameInstance::InitializeParty(AMyGameMode *gameMode)
{
  this->PartyManager = NewObject<UPartyManager>(UPartyManager::StaticClass());

  this->PartyManager->Start(this, gameMode);
}

void UMyGameInstance::AddItem(FName itemName, uint8 amount)
{
  for (UItemClass *item : this->Inventory)
  {
    if (item->Name.Replace(TEXT(" "), TEXT("")) == itemName)
    {
      item->AmountInInventory += amount;

      return;
    }
  }

  int32 itemPositon = this->Inventory.Num();

  FItemStruct *itemStructPointer = this->ItemsDataTable->FindRow<FItemStruct>(itemName, "", true);

  UItemClass *newItem = NewObject<UItemClass>(UItemClass::StaticClass());

  newItem->Create(itemPositon, amount, itemStructPointer, this);

  this->Inventory.Emplace(newItem);
}

void UMyGameInstance::RemoveItem(int32 positon)
{
  this->Inventory.RemoveAt(positon);

  for (uint8 i = 0; i < this->Inventory.Num(); i++)
  {
    UItemClass *item = this->Inventory[i];

    item->PositionInInventory = i;
  }
}

UMyGameInstance::UMyGameInstance()
{
  this->CurrentGameState = OVERWORLD;

  this->PartyManager = nullptr;

  const float DEFAULT_WEAK_ATTACK_ACCURAY = 92.f;

  const float DEFAULT_MEDIUM_ATTACK_ACCURAY = 82.f;

  const float DEFAULT_STRONG_ATTACK_ACCURAY = 72.f;

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_WEAK_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_MEDIUM_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_STRONG_ATTACK_ACCURAY);
}