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

  const float DEFAULT_WEAK_ATTACK_ACCURAY = 92.f;

  const float DEFAULT_MEDIUM_ATTACK_ACCURAY = 82.f;

  const float DEFAULT_STRONG_ATTACK_ACCURAY = 72.f;

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_WEAK_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_MEDIUM_ATTACK_ACCURAY);

  this->ATTACK_STRENGTH_ACCURACY_BASE.Emplace(DEFAULT_STRONG_ATTACK_ACCURAY);
}