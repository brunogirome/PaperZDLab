// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroClass.h"

#include "MyGameInstance.h"

void UHeroClass::Init(FHeroStruct *heroStructPointer, int32 level, UMyGameInstance *myGameInstance)
{
    FHeroStruct heroStructRef(heroStructPointer, level);

    this->HeroStruct = heroStructRef;

    this->Level = level;

    UMyGameInstance *gameInstance = myGameInstance;

    this->UCombatActorClass::init(&this->HeroStruct, myGameInstance);
}

UHeroClass::UHeroClass() {}
