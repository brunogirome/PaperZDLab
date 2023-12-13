// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"

#include "Kismet/GameplayStatics.h"

#include "PartyLeader.h"

#include "PartyMember.h"

#include "MyGameInstance.h"

#include "MyGameMode.h"

void UPartyManager::spawnAIHero()
{
    int32 currentPartySize = this->Heroes.Num();

    AHero *heroReferance =
        currentPartySize == 1 ? this->Leader : this->Heroes[currentPartySize - 1];

    FVector location = heroReferance->GetActorLocation();

    FRotator rotation = heroReferance->GetActorRotation();

    location.X -= 105;

    APartyMember *partyMember = this->gameMode->GetWorld()->SpawnActor<APartyMember>(APartyMember::StaticClass(), location, rotation);

    partyMember->TargetPawn = heroReferance;

    partyMember->ActorName = this->gameInstance->PartyRowNames[currentPartySize];

    partyMember->BeginPlay();

    this->Heroes.Emplace(partyMember);
}

void UPartyManager::Start(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef)
{
    this->gameInstance = gameInstanceRef;

    this->gameMode = gameModeRef;

    this->Leader = Cast<APartyLeader>(this->gameMode->GetWorld()->GetFirstPlayerController()->GetPawn());

    this->Leader->ActorName = this->gameInstance->PartyRowNames[0];

    this->Heroes.Emplace(this->Leader);

    for (int i = 1; i < this->gameInstance->PartyRowNames.Num(); i++)
    {
        this->spawnAIHero();
    }
}

UPartyManager::UPartyManager() {}