#pragma once

#include "CombatTypeEnum.h"

#include "ElementEnum.h"

#include "CombatActor.generated.h"

USTRUCT(BlueprintType)
struct FCombatActor : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Id"))
    int32 Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
    FString Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "CombatType"))
    TEnumAsByte<CombatTypeEnum> CombatType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Element"))
    TEnumAsByte<ElementEnum> Element;

    FCombatActor();

    FCombatActor(int32 id, FString name, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element);
};

