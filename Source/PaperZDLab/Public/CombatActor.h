#pragma once

#include "CombatTypeEnum.h"

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

    FCombatActor();

    FCombatActor(int32 id, FString name, TEnumAsByte<CombatTypeEnum> combatType);
};

