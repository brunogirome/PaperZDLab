#include "ACombatActor.h"

void ACombatActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Combat Actor");
}

ACombatActor::ACombatActor()
{
}