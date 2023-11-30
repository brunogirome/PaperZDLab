#include "ACombatActor.h"

void ACombatActor::BeginPlay()
{
    Super::BeginPlay();

    this->setupAIController();
}

void ACombatActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    this->actorAIController->MoveToActor(this->TargetPawn, 75.0f, false);
}

ACombatActor::ACombatActor()
{
    this->TargetPawn = nullptr;

    this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
}