#include "ACombatActor.h"

#include "AIController.h"

void ACombatActor::BeginPlay()
{
    Super::BeginPlay();

    if (!this->actorAIController)
    {
        this->actorAIController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    }

    if (this->TargetPawn && this->actorAIController)
    {
        this->AIControllerClass = this->actorAIController->GetClass();

        this->actorAIController->Possess(this);

        this->SpawnDefaultController();
    }
}

void ACombatActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    this->actorAIController->MoveToActor(this->TargetPawn, 50.0f, false);
}

ACombatActor::ACombatActor()
{
    this->actorAIController = nullptr;

    this->TargetPawn = nullptr;

    this->bUseControllerRotationYaw = false;

    this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
}