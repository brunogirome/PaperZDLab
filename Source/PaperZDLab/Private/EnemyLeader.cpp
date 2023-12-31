// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyLeader.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "Navigation/PathFollowingComponent.h"

#include "MyGameInstance.h"

#include "PartyManager.h"
#include "PartyLeader.h"
#include "Hero.h"

#include "EnemyPartyMember.h"
#include "EnemyStruct.h"

void AEnemyLeader::PositionHeroes()
{
    if (this->localGameInstance->CurrentGameState != OVERWORLD)
    {
        return;
    }

    this->localGameInstance->CurrentGameState = BATTLE;

    this->heroesGoalLocation.Empty();

    const float DISTANCE_X = 220.f;

    const float DISTANCE_Y = 420.f;

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

            newPositon.Y += 120.f;

            break;
        case 2:
            newPositon.X += DISTANCE_X * 0.5f;

            newPositon.Y += 120.f;

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

    AAIController *leaderController = this->GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

    // leaderController->bFindCameraComponentWhenViewTarget = false;

    // leaderController->Possess(this->partyLeader);

    leaderController->MoveToLocation(location);

    // FDelegateHandle MoveCompletedHandle = leaderController->ReceiveMoveCompleted.Add(OnMoveCompleted);

    UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->partyLeader->GetController(), location);

    for (int32 i = 1; i < (*this->heroesPointer).Num(); i++)
    {
        (*this->heroesPointer)[i]->GetController()->StopMovement();
    }

    for (int32 i = 1; i < (*this->heroesPointer).Num(); i++)
    {
        AAIController *heroController = (*this->heroesPointer)[i]->ActorAIController;

        location = getPosition(i);

        this->heroesGoalLocation.Emplace(location);

        UPathFollowingComponent *followPath = heroController->GetPathFollowingComponent();

        followPath->OnRequestFinished.AddUObject(this, &AEnemyLeader::TempOnComplete);

        heroController->MoveToLocation(location);
    }

    this->positioning = true;
}

void AEnemyLeader::TempOnComplete(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
    GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Yellow, "Complete yay");
}

void AEnemyLeader::SetupEnemies()
{
    this->enemies.Emplace(this);

    TArray<FName> otherEnemies;

    otherEnemies.Add("Skull");

    otherEnemies.Add("Skull");

    otherEnemies.Add("Skull");

    otherEnemies.Add("Skull");

    FVector currentLocation = this->GetActorLocation();

    FRotator currentRotation = this->GetActorRotation();

    for (int32 i = 0; i < otherEnemies.Num(); i++)
    {
        FVector spawnLocation = currentLocation;

        FVector battleLocation = currentLocation;

        float DISTANCE_X = 200.f;

        if (i == 0 || i % 2 == 0)
        {
            int32 multiplier = i == 0 ? 1 : i;

            spawnLocation.X -= 50.f;

            battleLocation.X -= DISTANCE_X * multiplier;
        }
        else
        {
            int32 multiplier = i == 1 ? 1 : i - 1;

            spawnLocation.X += 50.f;

            battleLocation.X += DISTANCE_X * multiplier;
        }

        AEnemyPartyMember *enemyPartyMember = this->GetWorld()->SpawnActor<AEnemyPartyMember>(AEnemyPartyMember::StaticClass(), currentLocation, currentRotation);

        FEnemyStruct *enemyStruct = this->localGameInstance->EnemiesDataTable->FindRow<FEnemyStruct>(otherEnemies[i], "", true);

        if (enemyStruct)
        {
            enemyPartyMember->Initialize(enemyStruct);
        }

        this->enemies.Emplace(enemyPartyMember);

        this->enemies[i + 1]->ActorAIController->MoveToLocation(battleLocation);
    }
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

            this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyLeader::SetHeroDirections, 0.2, false);

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

    this->SetupEnemies();

    FVector newPosition = this->partyLeader->CameraComp->GetComponentLocation();

    newPosition.X = this->GetActorLocation().X;

    this->partyLeader->CameraComp->SetWorldLocation(newPosition);
}

void AEnemyLeader::BeginPlay()
{
    Super::BeginPlay();

    if (!this->localGameInstance)
    {
        this->localGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this->GetWorld()));
    }

    if (!this->heroesPointer)
    {
        this->heroesPointer = &this->localGameInstance->PartyManager->Heroes;
    }

    if (!this->partyLeader)
    {
        this->partyLeader = localGameInstance->PartyManager->Leader;
    }

    FEnemyStruct *enemyStruct = this->localGameInstance->EnemiesDataTable->FindRow<FEnemyStruct>(this->ActorName, "", true);

    this->AEnemy::Initialize(enemyStruct);
}

AEnemyLeader::AEnemyLeader()
{
    this->localGameInstance = nullptr;

    this->positioning = false;
}