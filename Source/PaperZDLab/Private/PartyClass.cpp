// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyClass.h"

UPartyClass::UPartyClass() {}

void UPartyClass::Init(TArray<FName> partyRowNames, UDataTable *heroesDataDatable)
{
    for (FName memberName : partyRowNames)
    {
        int32 level = 1;

        FHeroStruct *heroStructPointer = heroesDataDatable->FindRow<FHeroStruct>(memberName, "", true);

        UHeroClass *heroInstance = NewObject<UHeroClass>(UHeroClass::StaticClass());

        heroInstance->Init(heroStructPointer, level);

        this->Members.Emplace(heroInstance);
    }
}

void UPartyClass::PrintHeroes()
{
    for (auto *hero : this->Members)
    {
        GEngine->AddOnScreenDebugMessage(-1, 35.0f, FColor::Yellow, hero->HeroStruct.Name);
    }
}