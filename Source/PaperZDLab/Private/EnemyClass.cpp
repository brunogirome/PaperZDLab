// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyClass.h"

void UEnemyClass::Init(FEnemyStruct *enemyStructPointerParam)
{
  this->EnemyStructPointer = enemyStructPointerParam;

  this->XpDrop = enemyStructPointerParam->XpDrop;

  this->UCombatActorClass::init(this->EnemyStructPointer);
}

UEnemyClass::UEnemyClass() {}