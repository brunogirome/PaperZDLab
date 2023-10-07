#pragma once

#include "ActorS.generated.h"

USTRUCT(BlueprintType)
struct FActorS : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BluePrintReadOnly, EditAnywhere, meta = (DisplayName = "Hp"))
    int32 Hp;

    FActorS();

    FActorS(int32 hp);
};
