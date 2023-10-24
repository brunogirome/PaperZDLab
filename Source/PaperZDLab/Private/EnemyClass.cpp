// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyClass.h"

void UEnemyClass::Init(FEnemyStruct *enemyStructPointerParam, UMyGameInstance *myGameInstance, uint8 battleInstancePosition)
{
  this->EnemyStructPointer = enemyStructPointerParam;

  this->XpDrop = enemyStructPointerParam->XpDrop;

  this->UCombatActorClass::init(this->EnemyStructPointer, myGameInstance);

  if (battleInstancePosition > 0)
  {
    this->Position = battleInstancePosition;
  }
}

UEnemyClass::UEnemyClass() {}