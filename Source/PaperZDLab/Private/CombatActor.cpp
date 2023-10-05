#include "CombatActor.h"

FCombatActor::FCombatActor()
{

}

FCombatActor::FCombatActor(int32 id, FString name, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element) 
{
    this->Id = id;
    this->Name = name;
    this->CombatType = combatType;
    this->Element = element;
}