// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatActorClass.h"

#include "HeroStruct.h"

#include "HeroClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UHeroClass : public UCombatActorClass
{
	GENERATED_BODY()

	FHeroStruct HeroStruct;

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Xp;

	UPROPERTY(BlueprintReadWrite)
	int32 Level;

	void Init(FHeroStruct *heroStructPointer, int32 level);

	UHeroClass();
};
