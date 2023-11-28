#include "ACombatActor.h"

#include "GameFramework/PlayerController.h"

#include "NavigationSystem.h"

#include "AIController.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameMode.h"

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

        this->AIMoveToTarget();
    }
}

void ACombatActor::AIMoveToTarget()
{
    if (this->TargetPawn)
    {
        this->actorAIController->MoveToActor(this->TargetPawn);
    }
}

void ACombatActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // this->AIMoveToTarget();
}

ACombatActor::ACombatActor()
{
    actorAIController = nullptr;
}