#include "HeroS.h"

FHeroS::FHeroS() {}

FHeroS::FHeroS(int32 hp, FString name)
    : FActorS(hp)
{
    this->Name = name;
};