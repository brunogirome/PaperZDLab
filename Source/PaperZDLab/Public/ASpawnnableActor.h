// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "PaperFlipbook.h"

#include "Components/CapsuleComponent.h"

#include "ASpawnnableActor.generated.h"

struct FFlipbookCollection
{
private:
	FString IdleUpFlipbookText;

	FString IdleDownFlipbookText;

	FString IdleRightFlipbookText;

	FString IdleLeftFlipbookText;

	FString MoveUpFlipbookText;

	FString MoveDownFlipbookText;

	FString MoveLeftFlipbookText;

	FString MoveRightFlipbookText;

public:
	UPaperFlipbook *IdleUpFlipbook;

	UPaperFlipbook *IdleDownFlipbook;

	UPaperFlipbook *IdleRightFlipbook;

	UPaperFlipbook *IdleLeftFlipbook;

	UPaperFlipbook *MoveUpFlipbook;

	UPaperFlipbook *MoveDownFlipbook;

	UPaperFlipbook *MoveLeftFlipbook;

	UPaperFlipbook *MoveRightFlipbook;

	FFlipbookCollection(FString ActorName)
	{
		IdleUpFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Idle_Up.FB_" + ActorName + "_Idle_Up'";

		IdleDownFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Idle_Down.FB_" + ActorName + "_Idle_Down'";

		IdleRightFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Idle_Right.FB_" + ActorName + "_Idle_Right'";

		IdleLeftFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Idle_Left.FB_" + ActorName + "_Idle_Left'";

		MoveUpFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Move_Up.FB_" + ActorName + "_Move_Up'";

		MoveDownFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Move_Down.FB_" + ActorName + "_Move_Down'";

		MoveLeftFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Move_Left.FB_" + ActorName + "_Move_Left'";

		MoveRightFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + ActorName + "/FB_" + ActorName + "_Move_Right.FB_" + ActorName + "_Move_Right'";

		IdleUpFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *IdleUpFlipbookText));

		IdleDownFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *IdleDownFlipbookText));

		IdleRightFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *IdleRightFlipbookText));

		IdleLeftFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *IdleLeftFlipbookText));

		MoveUpFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *MoveUpFlipbookText));

		MoveDownFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *MoveDownFlipbookText));

		MoveLeftFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *MoveLeftFlipbookText));

		MoveRightFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, *MoveRightFlipbookText));
	};

	FFlipbookCollection(){};
};

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

	// FString direction;

	float const UP_LEFT = -135.f;

	float const DOWN_LEFT = 135.f;

	float const UP_RIGHT = -45.f;

	float const DOWN_RIGHT = 45.f;

public:
	FName ActorName;

	FFlipbookCollection FlipBookCollection;

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
