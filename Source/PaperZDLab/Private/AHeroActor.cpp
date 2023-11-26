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

void AHeroActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHeroActor::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UInputAction *MoveAction = LoadObject<UInputAction>(nullptr, TEXT("InputAction'/Game/Character/Input/IA_Move.IA_Move'"));

    if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroActor::Move);
    }
}

void AHeroActor::Move(const FInputActionValue &Value)
{
    float x = Value[0];

    float y = Value[1];

    this->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), x, false);

    this->AddMovementInput(FVector(0.0f, -1.0f, 0.0f), y, false);
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