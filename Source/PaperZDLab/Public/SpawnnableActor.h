// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "PaperFlipbook.h"

#include "AIController.h"

#include "SpawnnableActor.generated.h"

class UMyGameInstance;

struct FFlipbookCollection
{
	UPaperFlipbook *IdleUpFlipbook;

	UPaperFlipbook *IdleDownFlipbook;

	UPaperFlipbook *IdleRightFlipbook;

	UPaperFlipbook *IdleLeftFlipbook;

	UPaperFlipbook *MoveUpFlipbook;

	UPaperFlipbook *MoveDownFlipbook;

	UPaperFlipbook *MoveLeftFlipbook;

	UPaperFlipbook *MoveRightFlipbook;

	FFlipbookCollection(FString actorName)
	{
		FString IdleUpFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Idle_Up.FB_" + actorName + "_Idle_Up'";

		FString IdleDownFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Idle_Down.FB_" + actorName + "_Idle_Down'";

		FString IdleRightFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Idle_Right.FB_" + actorName + "_Idle_Right'";

		FString IdleLeftFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Idle_Left.FB_" + actorName + "_Idle_Left'";

		FString MoveUpFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Move_Up.FB_" + actorName + "_Move_Up'";

		FString MoveDownFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Move_Down.FB_" + actorName + "_Move_Down'";

		FString MoveLeftFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Move_Left.FB_" + actorName + "_Move_Left'";

		FString MoveRightFlipbookText = "PaperFlipbook'/Game/Character/Aespa_Chars/FlipBooks/" + actorName + "/FB_" + actorName + "_Move_Right.FB_" + actorName + "_Move_Right'";

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

enum ECharacterDirectionStatus
{
	IDLE_UP,
	MOVE_UP,
	IDLE_DOWN,
	MOVE_DOWN,
	IDLE_LEFT,
	MOVE_LEFT,
	IDLE_RIGHT,
	MOVE_RIGHT
};

/**
 *
 */
UCLASS()
class PAPERZDLAB_API ASpawnnableActor : public APaperCharacter
{
	GENERATED_BODY()

	TEnumAsByte<ECharacterDirectionStatus> lastDirection;

	TEnumAsByte<ECharacterDirectionStatus> currentDirection;

	float const UP_LEFT = -135.f;

	float const DOWN_LEFT = 135.f;

	float const UP_RIGHT = -45.f;

	float const DOWN_RIGHT = 45.f;

protected:
	UMyGameInstance *gameInstance;

	FFlipbookCollection flipBookCollection;

	void initialize(FName actorName);

public:
	void setupAIController();

	UPROPERTY(BlueprintReadOnly)
	AAIController *ActorAIController;

	UPROPERTY(Editanywhere)
	FName ActorName;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void SetDirection(ECharacterDirectionStatus direction);

	ASpawnnableActor();
};
