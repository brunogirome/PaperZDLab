// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "EnemyStruct.h"

#include "Kismet/KismetStringLibrary.h"

void AEnemy::Initialize(FEnemyStruct *enemyStruct, uint8 battleInstancePosition)
{
    this->EnemyStruct = enemyStruct;

    this->XpDrop = this->EnemyStruct->XpDrop;

    for (FString moveset : this->EnemyStruct->Movesets)
    {
        TArray<FString> parsedMoveset;

        TArray<FAttackPatern> auxArray;

        moveset.ParseIntoArray(parsedMoveset, TEXT(","), true);

        for (FString move : parsedMoveset)
        {
            FString moveType = move.Mid(0, 1);

            if (moveType == "W")
            {
                auxArray.Emplace(FAttackPatern(WEAK_ATTACK));
            }
            else if (moveType == "M")
            {
                auxArray.Emplace(FAttackPatern(MEDIUM_ATTACK));
            }
            else if (moveType == "H")
            {
                auxArray.Emplace(FAttackPatern(HEAVY_ATTACK));
            }
            else if (moveType == "S")
            {
                FString spellPosition = move.Mid(1, 1);

                int32 spellPositionInt = UKismetStringLibrary::Conv_StringToInt(spellPosition);

                auxArray.Emplace(FAttackPatern(CAST_SPELL_MOVESET, spellPositionInt));
            }
        }

        this->Movesets.Emplace(auxArray);
    }

    if (battleInstancePosition > 0)
    {
        this->Position = battleInstancePosition;

        this->PositionForEnemyInBattle = battleInstancePosition;
    }

    this->ACombatActor::initialize(this->EnemyStruct);
}

AEnemy::AEnemy() {}