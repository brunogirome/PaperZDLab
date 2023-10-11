// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyClass.h"

UEnemyClass::UEnemyClass() {}

FEnemyStruct UEnemyClass::GetEnemyStruct()
{
  return *this->EnemyStruct;
}

void UEnemyClass::Init(FEnemyStruct *enemyStructPointer)
{
  this->EnemyStruct = enemyStructPointer;

  this->XpDrop = enemyStructPointer->XpDrop;

  this->UCombatActorClass::init(this->EnemyStruct);
}
