// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "Components/CapsuleComponent.h"

#include "ASpawnnableActor.generated.h"

struct FInputActionValue;

enum ECharacterDirection
{
	CHARACTER_UP,
	CHARACTER_DOWN,
	CHARACTER_LEFT,
	CHARACTER_RIGHT
};

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ASpawnnableActor : public APaperCharacter
{
	GENERATED_BODY()

	FString direction;

public:
	FName HeroName;

	bool IsMoving;

	class UPaperFlipbook *IdleUpFlipbook;

	class UPaperFlipbook *IdleDownFlipbook;

	class UPaperFlipbook *IdleLeftFlipbook;

	class UPaperFlipbook *IdleRightFlipbook;

	class UPaperFlipbook *MoveUpFlipbook;

	class UPaperFlipbook *MoveDownFlipbook;

	class UPaperFlipbook *MoveLeftFlipbook;

	class UPaperFlipbook *MoveRightFlipbook;

	TEnumAsByte<ECharacterDirection> CurrentDirection;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ASpawnnableActor();
};
