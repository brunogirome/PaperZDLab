// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnnableActor.h"

#include "Kismet/GameplayStatics.h"

#include "PaperFlipbookComponent.h"

#include "MyGameInstance.h"

void ASpawnnableActor::BeginPlay()
{
    Super::BeginPlay();
}

void ASpawnnableActor::initialize(FName actorName)
{
    if (!actorName.IsNone())
    {
        this->ActorName = actorName;

        this->flipBookCollection = FFlipbookCollection(this->ActorName.ToString());

        this->GetSprite()->SetFlipbook(flipBookCollection.IdleDownFlipbook);
    }
}

void ASpawnnableActor::setupAIController()
{
    if (!this->ActorAIController)
    {
        this->ActorAIController = this->GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

        this->ActorAIController->Possess(this);
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
            this->currentDirection = IDLE_UP;

            break;
        case MOVE_DOWN:
            this->currentDirection = IDLE_DOWN;

            break;
        case MOVE_LEFT:
            this->currentDirection = IDLE_LEFT;

            break;
        case MOVE_RIGHT:
            this->currentDirection = IDLE_RIGHT;

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

void ASpawnnableActor::SetDirection(ECharacterDirectionStatus direction)
{
    this->currentDirection = direction;
}

ASpawnnableActor::ASpawnnableActor()
{
    this->gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    this->GetSprite()->SetCastShadow(true);

    UMaterialInterface *MaskedLitSpriteMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Paper2D/MaskedLitSpriteMaterial.MaskedLitSpriteMaterial'"));

    FVector customLocation = this->GetSprite()->GetRelativeLocation();

    customLocation.Z = -60;

    this->GetSprite()->SetRelativeLocation(customLocation);

    this->GetSprite()->OverrideMaterials.Empty();

    this->GetSprite()->OverrideMaterials.Emplace(MaskedLitSpriteMaterial);

    this->GetCapsuleComponent()->SetCapsuleHalfHeight(54.0f);

    this->GetCapsuleComponent()->SetCapsuleRadius(30.0f);

    this->currentDirection = IDLE_DOWN;

    this->lastDirection = IDLE_DOWN;

    this->bUseControllerRotationYaw = false;

    this->ActorAIController = nullptr;
}