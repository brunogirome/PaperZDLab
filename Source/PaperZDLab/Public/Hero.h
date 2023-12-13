// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CombatActor.h"

#include "HeroStruct.h"

#include "Hero.generated.h"

/**
 *
 */
UCLASS()
class PAPERZDLAB_API AHero : public ACombatActor
{
	GENERATED_BODY()

	FHeroStruct HeroStruct;

public:
	uint8 Level;

	void Initialize(FHeroStruct *heroStruct, uint8 level);

	AHero();
};
