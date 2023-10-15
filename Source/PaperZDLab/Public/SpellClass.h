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
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	int32 ManaCost;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<SpellTypeEnum> SpellType;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<BuffTypeEnum> BuffType;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ElementEnum> Element;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<PartyBuffTypeEnum> PartyBuffType;

	UPROPERTY(EditAnywhere)
	int32 Amount;

	UPROPERTY(EditAnywhere)
	int32 Round;

	UPROPERTY(EditAnywhere)
	float Multiplier;

	USpellClass();

	void Init(FSpellStruct *spellStructPointer);
};
