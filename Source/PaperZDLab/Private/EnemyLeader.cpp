// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyLeader.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"

#include "MyGameInstance.h"

#include "PartyManager.h"
#include "PartyLeader.h"
#include "Hero.h"

void AEnemyLeader::PositionHeroes()
{
    if (this->localGameInstance->CurrentGameState != OVERWORLD)
    {
        return;
    }

    this->localGameInstance->CurrentGameState = BATTLE;

    this->heroesGoalLocation.Empty();

    const float DISTANCE_X = 150.f;

    const float DISTANCE_Y = 320.f;

    FVector enemyPositon = this->GetActorLocation();

    auto getPosition = [&](int32 position)
    {
        FVector newPositon = enemyPositon;

        newPositon.Y += DISTANCE_Y;

        switch (position)
        {
        case 0:
            newPositon.X -= DISTANCE_X * 1.5f;

            break;
        case 1:
            newPositon.X -= DISTANCE_X * 0.5f;

            break;
        case 2:
            newPositon.X += DISTANCE_X * 0.5f;

            break;
        case 3:
            newPositon.X += DISTANCE_X * 1.5f;

            break;
        default:
            break;
        }

        return newPositon;
    };

    FVector location = getPosition(0);

    this->heroesGoalLocation.Emplace(location);

    UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->partyLeader->GetController(), location);

    for (int32 i = 1; i < (*this->heroesPointer).Num(); i++)
    {
        (*this->heroesPointer)[i]->GetController()->StopMovement();
    }

    for (int32 i = 1; i < (*this->heroesPointer).Num(); i++)
    {
        location = getPosition(i);

        this->heroesGoalLocation.Emplace(location);

        (*this->heroesPointer)[i]->ActorAIController->MoveToLocation(location);
    }

    this->positioning = true;
}

void AEnemyLeader::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (this->positioning)
    {
        for (int32 i = 0; i < this->heroesGoalLocation.Num(); i++)
        {
            FVector heroLocation = (*this->heroesPointer)[i]->GetActorLocation();

            FheroesGoalLocation *goalLocation = &this->heroesGoalLocation[i];

            if (goalLocation->Reached)
            {
                continue;
            }

            if (!FVector::PointsAreNear(goalLocation->Location, heroLocation, 40))
            {
                continue;
            }

            goalLocation->Reached = true;

            FTimerHandle TimerHandle;

            this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyLeader::SetHeroDirections, 0.1, false);

            GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, (*this->heroesPointer)[i]->ActorName.ToString() + " is positioned!");
        }
    }
}

void AEnemyLeader::SetHeroDirections()
{
    bool everyoneInPosition = true;

    for (int32 i = 0; i < this->heroesPointer->Num(); i++)
    {
        if (!this->heroesGoalLocation[i].Reached)
        {
            everyoneInPosition = false;

            continue;
        }

        AHero *hero = (*this->heroesPointer)[i];

        ECharacterDirectionStatus newDirection = i < 2 ? IDLE_RIGHT : IDLE_LEFT;

        hero->SetDirection(newDirection);
    }

    if (!everyoneInPosition || !this->positioning)
    {
        return;
    }

    this->positioning = false;

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "AMONGUS");

    FVector newPosition = this->partyLeader->CameraComp->GetComponentLocation();

    newPosition.X = this->GetActorLocation().X;

    this->partyLeader->CameraComp->SetWorldLocation(newPosition);
}

void AEnemyLeader::BeginPlay()
{
    Super::BeginPlay();

    if (!this->localGameInstance)
    {
        this->localGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    }

    if (!this->heroesPointer)
    {
        this->heroesPointer = &this->localGameInstance->PartyManager->Heroes;
    }

    if (!this->partyLeader)
    {
        this->partyLeader = localGameInstance->PartyManager->Leader;
    }
}

AEnemyLeader::AEnemyLeader()
{
    this->localGameInstance = nullptr;

    this->positioning = false;
}