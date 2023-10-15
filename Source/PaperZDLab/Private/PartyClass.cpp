// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyClass.h"

void UPartyClass::Init(TArray<FName> partyRowNames)
{
    for (FName memberName : partyRowNames)
    {
        int32 level = 1;

        FHeroStruct *heroStructPointer = this->HeroesDataTable->FindRow<FHeroStruct>(memberName, "", true);

        UHeroClass *heroInstance = NewObject<UHeroClass>(UHeroClass::StaticClass());

        heroInstance->Init(heroStructPointer, level);

        this->Members.Emplace(heroInstance);
    }
}

void UPartyClass::PrintHeroes()
{
    for (auto *hero : this->Members)
    {
        GEngine->AddOnScreenDebugMessage(-1, 35.0f, FColor::Yellow, hero->Name);

        FString spells = TEXT("(");

        GEngine->AddOnScreenDebugMessage(-1, 35.0f, FColor::Blue, FString::FromInt(hero->Spells.Num()));

        for (auto &spellName : hero->Spells)
        {
            spells += spellName->Name + TEXT(", ");
        }

        spells += TEXT(")");

        GEngine->AddOnScreenDebugMessage(-1, 35.0f, FColor::Blue, spells);
    }
}

UPartyClass::UPartyClass()
{
    static ConstructorHelpers::FObjectFinder<UDataTable>
        Heroes_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Heroes_DataTable.Heroes_DataTable'"));

    this->HeroesDataTable = Heroes_DataTable_Ref.Object;
}