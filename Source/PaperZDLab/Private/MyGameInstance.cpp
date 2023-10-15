// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::InitParty(TArray<FName> partyRowNames)
{
  this->Party = NewObject<UPartyClass>(UPartyClass::StaticClass());

  this->Party->Init(partyRowNames);
}

UMyGameInstance::UMyGameInstance() {}