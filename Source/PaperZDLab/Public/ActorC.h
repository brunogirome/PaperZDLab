// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ActorS.h"

#include "ActorC.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PAPERZDLAB_API UActorC : public UObject
{
public:
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	bool isDead();

	UFUNCTION(BlueprintCallable)
	FActorS getActorS();

	FActorS* ActorS;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HpTotal;

	UActorC();

	UActorC(FActorS* actorS);
};
