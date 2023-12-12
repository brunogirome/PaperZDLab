#include "PartyMember.h"

void APartyMember::BeginPlay()
{
    Super::BeginPlay();

    this->setupAIController();
}

void APartyMember::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float distance = (this->GetActorLocation() - this->TargetPawn->GetActorLocation()).Size();

    if (distance >= 105)
    {
        this->actorAIController->MoveToActor(this->TargetPawn, 75.0f, false);
    }
}

APartyMember::APartyMember()
{
    this->TargetPawn = nullptr;

    this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
}