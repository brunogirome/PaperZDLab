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

    FEnemy(int32 id, FString name, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strength, int32 agility, int32 inteligence, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase, int32 xpDrop);
};
