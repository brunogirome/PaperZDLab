// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyClass.h"

#include "MyGameInstance.h"

void UPartyClass::Init(UMyGameInstance *myGameInstance)
{
    for (FName memberName : myGameInstance->PartyRowNames)
    {
        int32 level = 1;

        FHeroStruct *heroStructPointer = myGameInstance->HeroesDataTable->FindRow<FHeroStruct>(memberName, "", true);

        UHeroStats *heroInstance = NewObject<UHeroStats>(UHeroStats::StaticClass());

        heroInstance->Init(heroStructPointer, level, myGameInstance);

        this->Members.Add(heroInstance);
    }
}

UPartyClass::UPartyClass() {}