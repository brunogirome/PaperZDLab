// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpawnnableActor.h"

#include "PaperFlipbookComponent.h"

void ASpawnnableActor::BeginPlay()
{
    Super::BeginPlay();

    if (!this->ActorName.IsNone())
    {
        this->flipBookCollection = FFlipbookCollection(this->ActorName.ToString());

        this->GetSprite()->SetFlipbook(flipBookCollection.IdleDownFlipbook);
    }
}

void ASpawnnableActor::setupAIController()
{
    if (!this->actorAIController)
    {
        this->actorAIController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

        this->AIControllerClass = this->actorAIController->GetClass();

        this->actorAIController->Possess(this);

        this->SpawnDefaultController();
    }
}

void ASpawnnableActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector velocity = this->GetVelocity();

    UPaperFlipbook *newFlipbook = nullptr;

    if (velocity.IsNearlyZero())
    {

        switch (this->currentDirection)
        {
        case MOVE_UP:
            currentDirection = IDLE_UP;

            break;
        case MOVE_DOWN:
            currentDirection = IDLE_DOWN;

            break;
        case MOVE_LEFT:
            currentDirection = IDLE_LEFT;

            break;
        case MOVE_RIGHT:
            currentDirection = IDLE_RIGHT;

            break;
        }
    }
    else
    {
        float angle = FMath::Atan2(velocity.Y, velocity.X) * 180.0f / PI;

        float const TOLERANCE = 20.0f;

        this->lastDirection = this->currentDirection;

        if (angle <= UP_RIGHT - TOLERANCE && angle >= UP_LEFT + TOLERANCE)
        {
            this->currentDirection = MOVE_UP;
        }
        else if (angle >= this->DOWN_RIGHT + TOLERANCE && angle <= this->DOWN_LEFT - TOLERANCE)
        {
            this->currentDirection = MOVE_DOWN;
        }
        else if (angle <= this->DOWN_RIGHT + TOLERANCE && angle >= -(this->DOWN_LEFT - TOLERANCE))
        {
            this->currentDirection = MOVE_RIGHT;
        }
        else
        {
            this->currentDirection = MOVE_LEFT;
        }
    }

    if (this->lastDirection == this->currentDirection)
    {
        return;
    }

    switch (this->currentDirection)
    {
    case IDLE_UP:
        newFlipbook = this->flipBookCollection.IdleUpFlipbook;

        break;
    case IDLE_DOWN:
        newFlipbook = this->flipBookCollection.IdleDownFlipbook;

        break;
    case IDLE_LEFT:
        newFlipbook = this->flipBookCollection.IdleLeftFlipbook;

        break;
    case IDLE_RIGHT:
        newFlipbook = this->flipBookCollection.IdleRightFlipbook;

        break;
    case MOVE_UP:
        newFlipbook = this->flipBookCollection.MoveUpFlipbook;

        break;
    case MOVE_DOWN:
        newFlipbook = this->flipBookCollection.MoveDownFlipbook;

        break;
    case MOVE_LEFT:
        newFlipbook = this->flipBookCollection.MoveLeftFlipbook;

        break;
    case MOVE_RIGHT:
        newFlipbook = this->flipBookCollection.MoveRightFlipbook;

        break;
    }

    this->GetSprite()->SetFlipbook(newFlipbook);
}

ASpawnnableActor::ASpawnnableActor()
{
    this->GetSprite()->SetCastShadow(true);

    UMaterialInterface *MaskedLitSpriteMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Paper2D/MaskedLitSpriteMaterial.MaskedLitSpriteMaterial'"));

    this->GetSprite()->OverrideMaterials.Empty();

    this->GetSprite()->OverrideMaterials.Emplace(MaskedLitSpriteMaterial);

    this->GetCapsuleComponent()->SetCapsuleHalfHeight(54.0f);

    this->GetCapsuleComponent()->SetCapsuleRadius(30.0f);

    this->currentDirection = IDLE_DOWN;

    this->lastDirection = IDLE_DOWN;

    this->isMoving = false;

    this->bUseControllerRotationYaw = false;

    this->actorAIController = nullptr;
}