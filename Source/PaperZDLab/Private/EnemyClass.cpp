// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyClass.h"

UEnemyClass::UEnemyClass() {}

FEnemyStruct UEnemyClass::GetEnemyStruct()
{
  return *this->EnemyStruct;
}

void UEnemyClass::Init(FEnemyStruct *enemyStructPointer, int32 xpDrop)
{
  this->XpDrop = xpDrop;

  this->UCombatActorClass::init(this->EnemyStruct);
}
