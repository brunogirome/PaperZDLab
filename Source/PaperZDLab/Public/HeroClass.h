// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatActorClass.h"

#include "FHeroStruct.h"

#include "HeroClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UHeroClass : public UCombatActorClass
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FHeroStruct HeroStruct;

	UPROPERTY(BlueprintReadWrite)
	int32 Xp;

	UPROPERTY(BlueprintReadWrite)
	int32 Level;

	UFUNCTION(BlueprintCallable)
	void TempInitHeroStruct(FHeroStruct heroStructParam);

	UHeroClass();

	UHeroClass(FHeroStruct heroStruct);
};
