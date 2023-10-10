// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroClass.h"

void UHeroClass::TempInitHeroStruct(FHeroStruct heroStructParam)
{
    this->HeroStruct = heroStructParam;
    this->CombatActorStruct = heroStructParam;
}

UHeroClass::UHeroClass() {}

UHeroClass::UHeroClass(FHeroStruct heroStruct)
    : UCombatActorClass(heroStruct)
{
    this->HeroStruct = heroStruct;
}
