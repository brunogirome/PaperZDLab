// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyClass.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameModeBase.h"

UPartyClass::UPartyClass() {}

void UPartyClass::Init()
{
    AMyGameModeBase *game = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

    TArray<FName> partyRowNames = game->HeroesNames;

    UDataTable *heroesDataDatable = game->HeroesDataTable;

    for (FName memberName : partyRowNames)
    {
        int32 level = 1;

        FHeroStruct *heroStructPointer = heroesDataDatable->FindRow<FHeroStruct>(memberName, "", true);

        UHeroClass *heroInstance = NewObject<UHeroClass>(UHeroClass::StaticClass());

        heroInstance->Init(heroStructPointer, level);

        this->Members.Emplace(heroInstance);
    }
}
