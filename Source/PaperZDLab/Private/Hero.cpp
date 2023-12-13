// Fill out your copyright notice in the Description page of Project Settings.

#include "Hero.h"

#include "HeroStruct.h"

void AHero::Initialize(FHeroStruct *heroStruct, uint8 level)
{
    FHeroStruct heroStructRef(heroStruct, level);

    this->HeroStruct = heroStructRef;

    this->Level = level;

    this->ACombatActor::initialize(&this->HeroStruct);
}

AHero::AHero() {}
