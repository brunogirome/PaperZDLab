// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"

#include "PartyLeader.h"

#include "PartyMember.h"

#include "HeroStruct.h"

#include "MyGameMode.h"

FHeroStruct *UPartyManager::getHeroStruct(FName heroName)
{
    FHeroStruct *heroPointer = this->gameInstance->HeroesDataTable->FindRow<FHeroStruct>(heroName, "", true);

    return heroPointer ? heroPointer : nullptr;
}

void UPartyManager::spawnAIHero(FHeroStruct *heroStruct)
{
    int32 currentPartySize = this->Heroes.Num();

    AHero *heroReferance =
        currentPartySize == 1 ? this->Leader : this->Heroes[currentPartySize - 1];

    FVector location = heroReferance->GetActorLocation();

    FRotator rotation = heroReferance->GetActorRotation();

    location.X -= 105;

    APartyMember *partyMember = this->gameMode->GetWorld()->SpawnActor<APartyMember>(APartyMember::StaticClass(), location, rotation);

    partyMember->TargetPawn = heroReferance;

    partyMember->Initialize(heroStruct, 1);

    this->Heroes.Emplace(partyMember);
}

void UPartyManager::Start(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef)
{
    this->gameInstance = gameInstanceRef;

    this->gameMode = gameModeRef;

    bool isTheLeader = true;

    for (FName heroName : this->gameInstance->PartyRowNames)
    {
        FHeroStruct *heroStruct = this->getHeroStruct(heroName);

        if (isTheLeader)
        {
            this->Leader = Cast<APartyLeader>(this->gameMode->GetWorld()->GetFirstPlayerController()->GetPawn());

            this->Leader->Initialize(heroStruct, 1);

            isTheLeader = false;

            this->Heroes.Emplace(this->Leader);

            continue;
        }

        this->spawnAIHero(heroStruct);
    }
}

UPartyManager::UPartyManager() {}