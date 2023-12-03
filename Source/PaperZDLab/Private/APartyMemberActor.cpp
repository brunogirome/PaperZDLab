#include "APartyMemberActor.h"

void APartyMemberActor::BeginPlay()
{
    Super::BeginPlay();

    this->setupAIController();
}

void APartyMemberActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float location = (this->GetActorLocation() - this->TargetPawn->GetActorLocation()).Size();

    // GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, this->ActorName.ToString() + " distance: " + FString::SanitizeFloat(location));

    if (location >= 105)
    {
        // GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, this->ActorName.ToString() + " moving ");

        this->actorAIController->MoveToActor(this->TargetPawn, 75.0f, false);
    }
}

APartyMemberActor::APartyMemberActor()
{
    this->TargetPawn = nullptr;

    this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
}