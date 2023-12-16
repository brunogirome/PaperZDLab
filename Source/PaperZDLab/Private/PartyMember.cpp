#include "PartyMember.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameState.h"

void APartyMember::BeginPlay()
{
    Super::BeginPlay();

    this->setupAIController();
}

void APartyMember::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (this->localGameInstance->CurrentGameState != OVERWORLD)
    {
        return;
    }

    float distance = (this->GetActorLocation() - this->TargetPawn->GetActorLocation()).Size();

    if (distance >= 50)
    {
        this->ActorAIController->MoveToActor(this->TargetPawn, 50.0f, false);
    }
}

APartyMember::APartyMember()
{
    this->localGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    this->TargetPawn = nullptr;

    this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
}