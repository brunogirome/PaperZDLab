// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "ASpwannableActor.generated.h"

struct FInputActionValue;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AASpwannableActor : public APaperCharacter
{
	GENERATED_BODY()

	void setDirection();

	float movimentationX;

	float movimentationY;

public:
	bool IsMoving;

	virtual void BeginPlay() override;

	class UPaperFlipbook *IdleFlipBookUp;

	class UPaperFlipbook *IdleFlipBookRight;

	class UPaperFlipbook *IdleFlipBookDown;

	class UPaperFlipbook *IdleFlipBookLeft;

	class UPaperFlipbook *MoveFlipBookUp;

	class UPaperFlipbook *MoveFlipBookRight;

	class UPaperFlipbook *MoveFlipBookDown;

	class UPaperFlipbook *MoveFlipBookLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent *SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent *CameraComp;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent);

	void Move(const FInputActionValue &Value);

	void SetMoving();

	void SetNotMoving();

	AASpwannableActor();
};
