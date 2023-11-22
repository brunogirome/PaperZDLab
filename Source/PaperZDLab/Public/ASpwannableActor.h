// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInterface.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "InputActionValue.h"

#include "ASpwannableActor.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AASpwannableActor : public APaperCharacter
{
	GENERATED_BODY()

	void setDirection();

	class APlayerController *PlayerController;

	class UEnhancedInputLocalPlayerSubsystem *Subsystem;

	// class UEnhancedInputComponent *EnhancedInputComponent;

	float movimentationX;

	float movimentationY;

public:
	bool IsMoving;

	bool IsProtagonist;

	virtual void BeginPlay() override;

	UPaperFlipbook *IdleFlipBookUp;
	
	UPaperFlipbook *IdleFlipBookRight;

	UPaperFlipbook *IdleFlipBookDown;

	UPaperFlipbook *IdleFlipBookLeft;

	UPaperFlipbook *MoveFlipBookUp;

	UPaperFlipbook *MoveFlipBookRight;

	UPaperFlipbook *MoveFlipBookDown;

	UPaperFlipbook *MoveFlipBookLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USpringArmComponent *SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent *CameraComp;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent);

	class UInputMappingContext *MapContext;

	class UInputAction *MoveAction;

	void Move(const FInputActionValue &Value);

	void SetMoving();

	void SetNotMoving();

	AASpwannableActor();
};
