// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
 #include "ActorC.h"
 #include "HeroS.h"

#include "HeroC.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UHeroC : public UActorC
{
public:
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	FHeroS getHeroS();

	FHeroS* HeroS;

	UHeroC();

	UHeroC(FHeroS* heroS);
};
