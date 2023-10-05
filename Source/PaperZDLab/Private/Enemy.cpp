#include "Enemy.h"

FEnemy::FEnemy()
    : FCombatActor()
{

}

FEnemy::FEnemy(int32 id, FString name, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 xpDrop) 
   : FCombatActor(id, name, combatType, element)
{
    this->XpDrop = xpDrop;
}