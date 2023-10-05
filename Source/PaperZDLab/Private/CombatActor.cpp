#include "CombatActor.h"

FCombatActor::FCombatActor()
{

}

FCombatActor::FCombatActor(int32 id, FString name, TEnumAsByte<CombatTypeEnum> combatType) 
{
    this->Id = id;
    this->Name = name;
    this->CombatType = combatType;
}