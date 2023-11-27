#include "ACombatActor.h"

#include "NavigationSystem.h"

#include "Navigation/PathFollowingComponent.h"

#include "Tasks/AITask_MoveTo.h"

#include "Kismet/KismetMathLibrary.h"

void ACombatActor::BeginPlay()
{
    Super::BeginPlay();
}

void ACombatActor::FollowActor()
{
    aIController = this->GetController<AAIController>();
}

void ACombatActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IsLeader)
    {
        if (!alreadyPossessed)
        {
            aIController->Possess(this);

            alreadyPossessed = true;
        }

        aIController->MoveToActor(TargetPawn, 5.0f);
    }
}

ACombatActor::ACombatActor()
{
    if (!IsLeader)
    {
        aIController = CreateDefaultSubobject<AAIController>(TEXT("aIController"));

        this->bUseControllerRotationYaw = false;
    }
}