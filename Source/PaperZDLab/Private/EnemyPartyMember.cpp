// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPartyMember.h"

void AEnemyPartyMember::BeginPlay()
{
    Super::BeginPlay();

    // this->AEnemy::TempStart();
}

void AEnemyPartyMember::Initialize(FEnemyStruct *enemyStruct)
{
    this->AEnemy::Initialize(enemyStruct);
}

AEnemyPartyMember::AEnemyPartyMember()
{
}
