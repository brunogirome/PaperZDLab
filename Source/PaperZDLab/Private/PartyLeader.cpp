#include "PartyLeader.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInterface.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"

void APartyLeader::SetupControllerForBattle()
{
    this->setupAIController();
}

void APartyLeader::BeginPlay()
{
    Super::BeginPlay();

    APlayerController *PlayerController = Cast<APlayerController>(this->GetController());

    UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

    UInputMappingContext *MapContext = LoadObject<UInputMappingContext>(nullptr, TEXT("InputMappingContext'/Game/Character/Input/IMC_TopDown.IMC_TopDown'"));

    Subsystem->AddMappingContext(MapContext, 0);

    this->GetLocalViewingPlayerController()->bAutoManageActiveCameraTarget = false;
}

void APartyLeader::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APartyLeader::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UInputAction *MoveAction = LoadObject<UInputAction>(nullptr, TEXT("InputAction'/Game/Character/Input/IA_Move.IA_Move'"));

    if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APartyLeader::Move);
    }
}

void APartyLeader::Move(const FInputActionValue &Value)
{
    if (this->gameInstance->CurrentGameState != OVERWORLD)
    {
        return;
    }

    float x = Value[0];

    float y = Value[1];

    this->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), x, false);

    this->AddMovementInput(FVector(0.0f, -1.0f, 0.0f), y, false);
}

APartyLeader::APartyLeader()
{
    this->SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

    this->SpringArmComp->SetupAttachment(this->RootComponent);

    this->SpringArmComp->SetWorldRotation(FRotator(-25.0f, -90.0f, 0.0f));

    this->SpringArmComp->bDoCollisionTest = 0;

    this->CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

    this->CameraComp->SetupAttachment(this->SpringArmComp);

    this->CameraComp->SetRelativeLocation(FVector(-350.f, 0.0f, 0.0f));

    // this->CameraComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

    // CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
}