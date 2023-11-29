// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpawnnableActor.h"

#include "PaperFlipbookComponent.h"

void ASpawnnableActor::BeginPlay()
{
    Super::BeginPlay();

    if (!this->ActorName.IsNone())
    {
        this->FlipBookCollection = FFlipbookCollection(this->ActorName.ToString());

        this->IdleUpFlipbook = FlipBookCollection.IdleUpFlipbook;

        this->IdleDownFlipbook = FlipBookCollection.IdleDownFlipbook;

        this->IdleRightFlipbook = FlipBookCollection.IdleRightFlipbook;

        this->IdleLeftFlipbook = FlipBookCollection.IdleLeftFlipbook;

        this->MoveUpFlipbook = FlipBookCollection.MoveUpFlipbook;

        this->MoveDownFlipbook = FlipBookCollection.MoveDownFlipbook;

        this->MoveLeftFlipbook = FlipBookCollection.MoveLeftFlipbook;

        this->MoveRightFlipbook = FlipBookCollection.MoveRightFlipbook;

        this->GetSprite()->SetFlipbook(IdleDownFlipbook);
    }
}

void ASpawnnableActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector velocity = this->GetVelocity();

    float x = velocity.X;

    float y = velocity.Y;

    float angle = FMath::Atan2(y, x) * 180.0f / PI;

    UPaperFlipbook *newFlipbook = nullptr;

    if (velocity.IsNearlyZero())
    {
        switch (this->CurrentDirection)
        {
        case CHARACTER_UP:
            newFlipbook = this->IdleUpFlipbook;

            break;
        case CHARACTER_DOWN:
            newFlipbook = this->IdleDownFlipbook;

            break;
        case CHARACTER_LEFT:
            newFlipbook = this->IdleLeftFlipbook;

            break;
        case CHARACTER_RIGHT:
            newFlipbook = this->IdleRightFlipbook;

            break;
        }
    }
    else
    {
        float const TOLERANCE = 20.0f;

        if (angle <= UP_RIGHT - TOLERANCE && angle >= UP_LEFT + TOLERANCE)
        {
            this->CurrentDirection = CHARACTER_UP;

            newFlipbook = this->MoveUpFlipbook;

            // direction = "CHARACTER_UP";
        }
        else if (angle >= this->DOWN_RIGHT + TOLERANCE && angle <= this->DOWN_LEFT - TOLERANCE)
        {
            this->CurrentDirection = CHARACTER_DOWN;

            newFlipbook = this->MoveDownFlipbook;

            // direction = "CHARACTER_DOWN";
        }
        else if (angle <= this->DOWN_RIGHT + TOLERANCE && angle >= -(this->DOWN_LEFT - TOLERANCE))
        {
            this->CurrentDirection = CHARACTER_RIGHT;

            newFlipbook = this->MoveRightFlipbook;

            // direction = "CHARACTER_RIGHT";
        }
        else
        {
            this->CurrentDirection = CHARACTER_LEFT;

            newFlipbook = this->MoveLeftFlipbook;

            // direction = "CHARACTER_LEFT";
        }
    }

    this->GetSprite()->SetFlipbook(newFlipbook);

    // if (this->ActorName == "Karina")
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Velocity: X=" + FString::SanitizeFloat(x) + ", Y=" + FString::SanitizeFloat(y));

    //     GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Turquoise, "Angle 180: " + FString::SanitizeFloat(angle));

    //     GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::White, "Direction: " + direction);
    // }
}

ASpawnnableActor::ASpawnnableActor()
{
    this->GetSprite()->SetCastShadow(true);

    UMaterialInterface *MaskedLitSpriteMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Paper2D/MaskedLitSpriteMaterial.MaskedLitSpriteMaterial'"));

    this->GetSprite()->OverrideMaterials.Empty();

    this->GetSprite()->OverrideMaterials.Emplace(MaskedLitSpriteMaterial);

    this->GetCapsuleComponent()->SetCapsuleHalfHeight(54.0f);

    this->GetCapsuleComponent()->SetCapsuleRadius(30.0f);

    this->CurrentDirection = CHARACTER_DOWN;
}