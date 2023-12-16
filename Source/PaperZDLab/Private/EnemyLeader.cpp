// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyLeader.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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

    TArray<AHero *> *HeroesPointer = &localGameInstance->PartyManager->Heroes;

    APartyLeader *Leader = localGameInstance->PartyManager->Leader;

    UAIBlueprintHelperLibrary::SimpleMoveToLocation(Leader->GetController(), getPosition(0));

    for (int32 i = 1; i < (*HeroesPointer).Num(); i++)
    {
        (*HeroesPointer)[i]->GetController()->StopMovement();
    }

    for (int32 i = 1; i < (*HeroesPointer).Num(); i++)
    {
        (*HeroesPointer)[i]->ActorAIController->MoveToLocation(getPosition(i));
    }
}

void AEnemyLeader::BeginPlay()
{
    Super::BeginPlay();

    if (!this->localGameInstance)
    {
        this->localGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    }
}

AEnemyLeader::AEnemyLeader()
{
    this->localGameInstance = nullptr;
}