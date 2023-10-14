#pragma once

#include "SpellTypeEnum.h"
#include "BuffTypeEnum.h"
#include "ElementEnum.h"
#include "PartyBuffTypeEnum.h"

#include "SpellStruct.generated.h"

USTRUCT(BlueprintType)
struct FSpellStruct : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere)
  FString Name;

  UPROPERTY(EditAnywhere)
  FString Description;

  UPROPERTY(EditAnywhere)
  int32 ManaCost;

  UPROPERTY(EditAnywhere)
  TEnumAsByte<SpellTypeEnum> SpellType;

  UPROPERTY(EditAnywhere)
  TEnumAsByte<BuffTypeEnum> BuffType;

  UPROPERTY(EditAnywhere)
  TEnumAsByte<ElementEnum> Element;

  UPROPERTY(EditAnywhere)
  TEnumAsByte<PartyBuffTypeEnum> PartyBuffType;

  UPROPERTY(EditAnywhere)
  int32 Amount;

  UPROPERTY(EditAnywhere)
  int32 Round;

  UPROPERTY(EditAnywhere)
  float Multiplier;

  FSpellStruct();
};