// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "Components/CapsuleComponent.h"

#include "ASpawnnableActor.generated.h"

struct FInputActionValue;

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ASpawnnableActor : public APaperCharacter
{
	GENERATED_BODY()

public:
	bool IsMoving;

	float MovimentationX;

	float MovimentationY;

	class UPaperFlipbook *IdleFlipBookUp;

	class UPaperFlipbook *IdleFlipBookRight;

	class UPaperFlipbook *IdleFlipBookDown;

	class UPaperFlipbook *IdleFlipBookLeft;

	class UPaperFlipbook *MoveFlipBookUp;

	class UPaperFlipbook *MoveFlipBookRight;

	class UPaperFlipbook *MoveFlipBookDown;

	class UPaperFlipbook *MoveFlipBookLeft;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void SetDirection();

	ASpawnnableActor();
};
