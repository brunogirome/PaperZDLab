// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ItemStruct.h"

#include "ItemClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UItemClass : public UObject
{
  GENERATED_BODY()

  class UMyGameInstance *gameInstance;

public:
  UPROPERTY(BluePrintReadOnly)
  int32 PositionInInventory;

  UPROPERTY(BluePrintReadOnly)
  bool IsEquiped;

  // UPROPERTY(BluePrintReadOnly)
  // class UHeroStats *HeroEquipped;

  UPROPERTY(BluePrintReadOnly)
  FString Name;

  UPROPERTY(BluePrintReadOnly)
  FString Description;

  UPROPERTY(BluePrintReadOnly)
  TEnumAsByte<ItemTypeEnum> ItemType;

  UPROPERTY(BluePrintReadOnly)
  TEnumAsByte<ArtifactTypeEnum> ArtifactType;

  UPROPERTY(BluePrintReadOnly)
  TEnumAsByte<ConsumableTypeEnum> ConsumableType;

  UPROPERTY(BluePrintReadOnly)
  FString ItemKey;

  UPROPERTY(BluePrintReadOnly)
  int32 ItemPrice;

  UPROPERTY(BluePrintReadOnly)
  int32 AmountInInventory;

  UPROPERTY(BluePrintReadOnly)
  int32 StrengthFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float StrengthPercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 AgilityFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float AgilityPercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 InteligenceFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float InteligencePercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 PhysicalDamageFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float PhysicalDamagePercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 MagicDamageFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float MagicDamagePercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 PhysicalDefenseFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float PhysicalDefensePercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 MagicDefenseFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float MagicDefensePercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 HpFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float HpPercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 ManaFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float ManaPercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 SpeedFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float SpeedPercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 StaminaFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float StaminaPercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 EvasionFlatBonus;

  UPROPERTY(BluePrintReadOnly)
  float EvasionPercentageBonus;

  UPROPERTY(BluePrintReadOnly)
  int32 ConsumableHealing;

  UItemClass();

  void Create(int32 positon, int32 amount, FItemStruct *itemStructPointer, UMyGameInstance *myGameInstance);

  void Consume(int32 amount = 1);
};