// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpwannableActor.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

#include "EnhancedInputSubsystems.h"

void AASpwannableActor::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = Cast<APlayerController>(this->GetController());

    Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

    MapContext = LoadObject<UInputMappingContext>(nullptr, TEXT("InputMappingContext'/Game/Character/Input/IMC_TopDown.IMC_TopDown'"));

    Subsystem->AddMappingContext(MapContext, 0);
}

void AASpwannableActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AASpwannableActor::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    MoveAction = LoadObject<UInputAction>(nullptr, TEXT("InputAction'/Game/Character/Input/IA_Move.IA_Move'"));

    if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AASpwannableActor::Move);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AASpwannableActor::SetMoving);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AASpwannableActor::SetNotMoving);
    }
}

void AASpwannableActor::Move(const FInputActionValue &Value)
{
    movimentationX = Value[0];

    movimentationY = Value[1];

    if (movimentationX != 0 && movimentationY != 0)
    {
        this->GetSprite()->SetFlipbook(movimentationX == 1 ? MoveFlipBookRight : MoveFlipBookLeft);
    }
    else if (movimentationX == 0)
    {
        this->GetSprite()->SetFlipbook(movimentationY == 1 ? MoveFlipBookUp : MoveFlipBookDown);
    }
    else if (movimentationY == 0)
    {
        this->GetSprite()->SetFlipbook(movimentationX == 1 ? MoveFlipBookRight : MoveFlipBookLeft);
    }

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Turquoise, Value.ToString());

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Turquoise, FString::SanitizeFloat(Value[0]));

    GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Turquoise, FString::SanitizeFloat(Value[1]));
}

void AASpwannableActor::SetMoving()
{
    this->IsMoving = true;
}

void AASpwannableActor::SetNotMoving()
{
    this->IsMoving = false;

    if (movimentationX != 0 && movimentationY != 0)
    {
        this->GetSprite()->SetFlipbook(movimentationX == 1 ? IdleFlipBookRight : IdleFlipBookLeft);
    }
    else if (movimentationX == 0)
    {
        this->GetSprite()->SetFlipbook(movimentationY == 1 ? IdleFlipBookUp : IdleFlipBookDown);
    }
    else if (movimentationY == 0)
    {
        this->GetSprite()->SetFlipbook(movimentationX == 1 ? IdleFlipBookRight : IdleFlipBookLeft);
    }
}

AASpwannableActor::AASpwannableActor()
{
    IdleFlipBookUp = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Idle_Up.Karina_Idle_Up'"));

    IdleFlipBookRight = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Idle_Right.Karina_Idle_Right'"));

    IdleFlipBookDown = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Idle_Down.Karina_Idle_Down'"));

    IdleFlipBookLeft = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Idle_Left.Karina_Idle_Left'"));

    MoveFlipBookUp = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Move_Up.Karina_Move_Up'"));

    MoveFlipBookRight = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Move_Right.Karina_Move_Right'"));

    MoveFlipBookDown = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Move_Down.Karina_Move_Down'"));

    MoveFlipBookLeft = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/Karina/Karina_Move_Left.Karina_Move_Left'"));

    this->GetSprite()->SetFlipbook(IdleFlipBookDown);

    this->GetSprite()->SetCastShadow(true);

    UMaterialInterface *MaskedLitSpriteMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Paper2D/MaskedLitSpriteMaterial.MaskedLitSpriteMaterial'"));

    this->GetSprite()->OverrideMaterials.Empty();

    this->GetSprite()->OverrideMaterials.Emplace(MaskedLitSpriteMaterial);

    this->GetCapsuleComponent()->SetCapsuleHalfHeight(54.0f);

    this->GetCapsuleComponent()->SetCapsuleRadius(30.0f);

    this->IsProtagonist = true;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

    CameraComp->SetupAttachment(GetCapsuleComponent());

    CameraComp->SetRelativeLocation(FVector(-350.f, 0.0f, 0.0f));

    CameraComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

    SpringArmComp->SetupAttachment(GetCapsuleComponent());

    SpringArmComp->SetRelativeRotation(FRotator(-25.0f, -90.0f, 0.0f));
    // FRotator = Y, Z, X

    CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
}