#pragma once

#include "ItemTypeEnum.h"
#include "ArtifactTypeEnum.h"
#include "ConsumableTypeEnum.h"

#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere)
  FString Name;

  UPROPERTY(EditAnywhere)
  FString Description;

  UPROPERTY(EditAnywhere)
  TEnumAsByte<ItemTypeEnum> ItemType;

  UPROPERTY(EditAnywhere)
  TEnumAsByte<ArtifactTypeEnum> ArtifactType;

  UPROPERTY(EditAnywhere)
  TEnumAsByte<ConsumableTypeEnum> ConsumableType;

  UPROPERTY(EditAnywhere)
  int32 ItemPrice;

  UPROPERTY(EditAnywhere)
  FString ItemKey;

  UPROPERTY(EditAnywhere)
  int32 StrengthFlatBonus;

  UPROPERTY(EditAnywhere)
  float StrengthPercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 AgilityFlatBonus;

  UPROPERTY(EditAnywhere)
  float AgilityPercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 InteligenceFlatBonus;

  UPROPERTY(EditAnywhere)
  float InteligencePercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 PhysicalDamageFlatBonus;

  UPROPERTY(EditAnywhere)
  float PhysicalDamagePercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 MagicDamageFlatBonus;

  UPROPERTY(EditAnywhere)
  float MagicDamagePercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 PhysicalDefenseFlatBonus;

  UPROPERTY(EditAnywhere)
  float PhysicalDefensePercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 MagicDefenseFlatBonus;

  UPROPERTY(EditAnywhere)
  float MagicDefensePercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 HpFlatBonus;

  UPROPERTY(EditAnywhere)
  float HpPercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 ManaFlatBonus;

  UPROPERTY(EditAnywhere)
  float ManaPercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 SpeedFlatBonus;

  UPROPERTY(EditAnywhere)
  float SpeedPercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 StaminaFlatBonus;

  UPROPERTY(EditAnywhere)
  float StaminaPercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 EvasionFlatBonus;

  UPROPERTY(EditAnywhere)
  float EvasionPercentageBonus;

  UPROPERTY(EditAnywhere)
  int32 ConsumableHealing;

  FItemStruct();
};