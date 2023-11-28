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

        // this->actorAIController->GetPathFollowingComponent();

        // FScriptDelegate AIMoveToTargetDelegate;

        // AIMoveToTargetDelegate.BindUFunction(this, "Amongus2SoonTm");

        // this->actorAIController->ReceiveMoveCompleted.Add(AIMoveToTargetDelegate);

        this->SpawnDefaultController();

        this->AIMoveToTarget();
    }
}

void ACombatActor::AIMoveToTarget()
{
    if (this->TargetPawn)
    {
        this->actorAIController->MoveToActor(this->TargetPawn, 50.0f, false);
    }
}

void ACombatActor::Amongus2SoonTm()
{
    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "SO CREEP TOONIGHT");
}

void ACombatActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

ACombatActor::ACombatActor()
{
    this->actorAIController = nullptr;

    this->TargetPawn = nullptr;
}