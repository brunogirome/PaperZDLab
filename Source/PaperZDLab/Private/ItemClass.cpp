// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemClass.h"

#include "MyGameInstance.h"

void UItemClass::Create(int32 positon, int32 amount, FItemStruct *itemStructPointer, UMyGameInstance *myGameInstance)
{
    this->gameInstance = myGameInstance;

    this->PositionInInventory = positon;

    this->AmountInInventory = amount;

    this->IsEquiped = false;

    this->Name = itemStructPointer->Name;

    this->Description = itemStructPointer->Description;

    this->ItemType = itemStructPointer->ItemType;

    this->ArtifactType = itemStructPointer->ArtifactType;

    this->ConsumableType = itemStructPointer->ConsumableType;

    this->ItemKey = itemStructPointer->ItemKey;

    this->ItemPrice = itemStructPointer->ItemPrice;

    this->StrengthFlatBonus = itemStructPointer->StrengthFlatBonus;

    this->StrengthPercentageBonus = itemStructPointer->StrengthPercentageBonus;

    this->AgilityFlatBonus = itemStructPointer->AgilityFlatBonus;

    this->AgilityPercentageBonus = itemStructPointer->AgilityPercentageBonus;

    this->InteligenceFlatBonus = itemStructPointer->InteligenceFlatBonus;

    this->InteligencePercentageBonus = itemStructPointer->InteligencePercentageBonus;

    this->PhysicalDamageFlatBonus = itemStructPointer->PhysicalDamageFlatBonus;

    this->PhysicalDamagePercentageBonus = itemStructPointer->PhysicalDamagePercentageBonus;

    this->MagicDamageFlatBonus = itemStructPointer->MagicDamageFlatBonus;

    this->MagicDamagePercentageBonus = itemStructPointer->MagicDamagePercentageBonus;

    this->PhysicalDefenseFlatBonus = itemStructPointer->PhysicalDefenseFlatBonus;

    this->PhysicalDefensePercentageBonus = itemStructPointer->PhysicalDefensePercentageBonus;

    this->MagicDamageFlatBonus = itemStructPointer->MagicDamageFlatBonus;

    this->MagicDamagePercentageBonus = itemStructPointer->MagicDamagePercentageBonus;

    this->HpFlatBonus = itemStructPointer->HpFlatBonus;

    this->HpPercentageBonus = itemStructPointer->HpPercentageBonus;

    this->ManaFlatBonus = itemStructPointer->ManaFlatBonus;

    this->ManaPercentageBonus = itemStructPointer->ManaPercentageBonus;

    this->SpeedFlatBonus = itemStructPointer->SpeedFlatBonus;

    this->SpeedPercentageBonus = itemStructPointer->SpeedPercentageBonus;

    this->StaminaFlatBonus = itemStructPointer->StaminaFlatBonus;

    this->StaminaPercentageBonus = itemStructPointer->StaminaPercentageBonus;

    this->EvasionFlatBonus = itemStructPointer->EvasionFlatBonus;

    this->EvasionPercentageBonus = itemStructPointer->EvasionPercentageBonus;

    this->ConsumableHealing = itemStructPointer->ConsumableHealing;
}

void UItemClass::Consume(int32 amount)
{
    this->AmountInInventory -= amount;

    if (this->AmountInInventory <= 0)
    {
        this->gameInstance->RemoveItem(this->PositionInInventory);
    }
}

UItemClass::UItemClass() {}
