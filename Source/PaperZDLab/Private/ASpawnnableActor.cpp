// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpawnnableActor.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

void ASpawnnableActor::BeginPlay()
{
    Super::BeginPlay();

    IdleUpFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Up.FB_Karina_Idle_Up'"));

    IdleDownFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Down.FB_Karina_Idle_Down'"));

    IdleRightFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Right.FB_Karina_Idle_Right'"));

    IdleLeftFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Left.FB_Karina_Idle_Left'"));

    MoveUpFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Up.FB_Karina_Move_Up'"));

    MoveDownFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Down.FB_Karina_Move_Down'"));

    MoveLeftFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Left.FB_Karina_Move_Left'"));

    MoveRightFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Right.FB_Karina_Move_Right'"));

    this->GetSprite()->SetFlipbook(IdleDownFlipbook);
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
        if (angle <= -70 && angle >= -110)
        {
            this->CurrentDirection = CHARACTER_UP;

            newFlipbook = this->MoveUpFlipbook;

            direction = "CHARACTER_UP";
        }
        else if (angle >= 70 && angle <= 110)
        {
            this->CurrentDirection = CHARACTER_DOWN;

            newFlipbook = this->MoveDownFlipbook;

            direction = "CHARACTER_DOWN";
        }
        else if (angle <= 70 && angle >= -110)
        {
            this->CurrentDirection = CHARACTER_RIGHT;

            newFlipbook = this->MoveRightFlipbook;

            direction = "CHARACTER_RIGHT";
        }
        else
        {
            this->CurrentDirection = CHARACTER_LEFT;

            newFlipbook = this->MoveLeftFlipbook;

            direction = "CHARACTER_LEFT";
        }
    }

    this->GetSprite()->SetFlipbook(newFlipbook);

    // GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Velocity: X=" + FString::SanitizeFloat(x) + ", Y=" + FString::SanitizeFloat(y));

    // GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Turquoise, "Angle: " + FString::SanitizeFloat(angle));

    // GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::White, "Direction: " + direction);
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