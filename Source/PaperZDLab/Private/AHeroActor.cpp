#include "AHeroActor.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInterface.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AHeroActor::BeginPlay()
{
    Super::BeginPlay();

    APlayerController *PlayerController = Cast<APlayerController>(this->GetController());

    UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

    UInputMappingContext *MapContext = LoadObject<UInputMappingContext>(nullptr, TEXT("InputMappingContext'/Game/Character/Input/IMC_TopDown.IMC_TopDown'"));

    Subsystem->AddMappingContext(MapContext, 0);
}

void AHeroActor::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UInputAction *MoveAction = LoadObject<UInputAction>(nullptr, TEXT("InputAction'/Game/Character/Input/IA_Move.IA_Move'"));

    if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroActor::Move);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AHeroActor::SetMoving);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AHeroActor::SetNotMoving);
    }
}

void AHeroActor::Move(const FInputActionValue &Value)
{
    this->MovimentationX = Value[0];

    this->MovimentationY = Value[1];

    SetDirection();

    this->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovimentationX, false);

    this->AddMovementInput(FVector(0.0f, -1.0f, 0.0f), MovimentationY, false);
}

void AHeroActor::SetMoving()
{
    this->IsMoving = true;
}

void AHeroActor::SetNotMoving()
{
    this->IsMoving = false;

    SetDirection();
}

AHeroActor::AHeroActor()
{

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

    CameraComp->SetupAttachment(GetCapsuleComponent());

    CameraComp->SetRelativeLocation(FVector(-350.f, 0.0f, 0.0f));

    CameraComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

    SpringArmComp->SetupAttachment(GetCapsuleComponent());

    SpringArmComp->SetRelativeRotation(FRotator(-25.0f, -90.0f, 0.0f));
    // FRotator = Y, Z, X

    SpringArmComp->bDoCollisionTest = 0;

    CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
}