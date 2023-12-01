#include "APartyMemberActor.h"

void APartyMemberActor::BeginPlay()
{
    Super::BeginPlay();

    this->setupAIController();
}

void APartyMemberActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    this->actorAIController->MoveToActor(this->TargetPawn, 75.0f, false);
}

APartyMemberActor::APartyMemberActor()
{
    this->TargetPawn = nullptr;

    this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
}