#pragma once

#include "CombatActor.h"

#include "Enemy.generated.h"

USTRUCT(BlueprintType)
struct FEnemy : public FCombatActor
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "XpDrop"))
    int32 XpDrop;

    FEnemy();

    FEnemy(int32 id, FString name, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 xpDrop);
};

