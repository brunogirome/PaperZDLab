// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "SpellStruct.h"

#include "SpellClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API USpellClass : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BluePrintReadOnly)
	FString Name;

	UPROPERTY(BluePrintReadOnly)
	FString Description;

	UPROPERTY(BluePrintReadOnly)
	int32 ManaCost;

	UPROPERTY(BluePrintReadOnly)
	TEnumAsByte<SpellTypeEnum> SpellType;

	UPROPERTY(BluePrintReadOnly)
	TEnumAsByte<BuffTypeEnum> BuffType;

	UPROPERTY(BluePrintReadOnly)
	TEnumAsByte<ElementEnum> Element;

	UPROPERTY(BluePrintReadOnly)
	TEnumAsByte<PartyBuffTypeEnum> PartyBuffType;

	UPROPERTY(BluePrintReadOnly)
	int32 Amount;

	UPROPERTY(BluePrintReadOnly)
	int32 Round;

	UPROPERTY(BluePrintReadOnly)
	uint8 RemainingRounds;

	UPROPERTY(BluePrintReadOnly)
	uint8 PositionInActorSpells;

	UPROPERTY(BluePrintReadOnly)
	float Multiplier;

	USpellClass();

	uint8 GetRoundsForCasting();

	bool IsBuffExpired();

	void Init(FSpellStruct *spellStructPointer, uint8 position);

	void ResetRounds();

	void DecreaseRounds(uint8 amount = 1);

	void IncreaseRounds(uint8 amount = 1);
};
