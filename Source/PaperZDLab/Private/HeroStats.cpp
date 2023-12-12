// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroStats.h"

#include "MyGameInstance.h"

void UHeroStats::Init(FHeroStruct *heroStructPointer, int32 level, UMyGameInstance *myGameInstance)
{
    FHeroStruct heroStructRef(heroStructPointer, level);

    this->HeroStruct = heroStructRef;

    this->Level = level;

    this->UCombatActorStats::init(&this->HeroStruct, myGameInstance);
}

UHeroStats::UHeroStats() {}
