// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

// void UMyGameInstance::Init()
// {
//   Super::Init();
// }

void UMyGameInstance::InitParty()
{
  this->Party = NewObject<UPartyClass>(UPartyClass::StaticClass());

  this->Party->Init(this);
}

UMyGameInstance::UMyGameInstance()
{
  this->CurrentGameState = OVERWORLD;

  this->Party = nullptr;
}