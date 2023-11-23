// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpawnnableActor.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

void ASpawnnableActor::BeginPlay()
{
    Super::BeginPlay();

    IdleFlipBookUp = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Up.FB_Karina_Idle_Up'"));

    IdleFlipBookRight = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Right.FB_Karina_Idle_Right'"));

    IdleFlipBookDown = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Down.FB_Karina_Idle_Down'"));

    IdleFlipBookLeft = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Idle_Left.FB_Karina_Idle_Left'"));

    MoveFlipBookUp = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Up.FB_Karina_Move_Up'"));

    MoveFlipBookRight = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Right.FB_Karina_Move_Right'"));

    MoveFlipBookDown = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Down.FB_Karina_Move_Down'"));

    MoveFlipBookLeft = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/FB_Karina_Move_Left.FB_Karina_Move_Left'"));

    this->GetSprite()->SetFlipbook(IdleFlipBookDown);
}

void ASpawnnableActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, "Spawn Actor");
}

void ASpawnnableActor::SetDirection()
{
    UPaperFlipbook *newFlipbook = nullptr;

    if (MovimentationX != 0 && MovimentationY != 0)
    {
        if (this->IsMoving)
        {
            newFlipbook = MovimentationX == 1 ? MoveFlipBookRight : MoveFlipBookLeft;
        }
        else
        {
            newFlipbook = MovimentationX == 1 ? IdleFlipBookRight : IdleFlipBookLeft;
        }
    }
    else if (MovimentationX == 0)
    {
        if (this->IsMoving)
        {
            newFlipbook = MovimentationY == 1 ? MoveFlipBookUp : MoveFlipBookDown;
        }
        else
        {
            newFlipbook = MovimentationY == 1 ? IdleFlipBookUp : IdleFlipBookDown;
        }
    }
    else if (MovimentationY == 0)
    {
        if (this->IsMoving)
        {
            newFlipbook = MovimentationX == 1 ? MoveFlipBookRight : MoveFlipBookLeft;
        }
        else
        {
            newFlipbook = MovimentationX == 1 ? IdleFlipBookRight : IdleFlipBookLeft;
        }
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
}