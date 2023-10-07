#pragma once

#include "ActorS.h"

#include "HeroS.generated.h"

USTRUCT(BlueprintType)
struct FHeroS : public FActorS
{
    GENERATED_BODY()

    UPROPERTY(BluePrintReadOnly, EditAnywhere, meta = (DisplayName = "Name"))
    FString Name;

    FHeroS();

    FHeroS(int32 hp, FString name);
};
