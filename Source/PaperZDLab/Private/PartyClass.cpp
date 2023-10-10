// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyClass.h"

UPartyClass::UPartyClass()
{
    static ConstructorHelpers::FObjectFinder<UDataTable>
        Heroes_DataTable_Ref(TEXT("DataTable'/Game/DataTables/Heroes_DataTable.Heroes_DataTable'"));

    HeroesDataTable = Heroes_DataTable_Ref.Object;
}

UPartyClass::UPartyClass(TArray<FName> initialMembersNames)
{
    this->MembersRowName = initialMembersNames;
}

void UPartyClass::LoadMembers()
{
    std::vector<FName> initialParty;

    initialParty.push_back(FName(TEXT("Karina")));
    initialParty.push_back(FName(TEXT("Winter")));
    initialParty.push_back(FName(TEXT("Giselle")));
    initialParty.push_back(FName(TEXT("NingNing")));

    for (FName memberName : initialParty)
    {
        int32 level = 1;

        FHeroStruct *heroStructPointer = this->HeroesDataTable->FindRow<FHeroStruct>(memberName, "", true);

        FHeroStruct heroStructRef(heroStructPointer, level);

        UHeroClass *heroInstance = NewObject<UHeroClass>(UHeroClass::StaticClass());

        heroInstance->Init(heroStructRef);

        this->Members.Emplace(heroInstance);
    }
}
