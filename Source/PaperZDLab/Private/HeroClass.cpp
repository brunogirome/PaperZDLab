// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroClass.h"

void UHeroClass::Init(FHeroStruct *heroStructPointer, int32 level, UDataTable *spellsDataTable)
{
    FHeroStruct heroStructRef(heroStructPointer, level);

    this->HeroStruct = heroStructRef;

    this->Level = level;

    this->UCombatActorClass::init(&this->HeroStruct, spellsDataTable);
}

UHeroClass::UHeroClass() {}
