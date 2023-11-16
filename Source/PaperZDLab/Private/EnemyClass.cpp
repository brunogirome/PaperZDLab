// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyClass.h"

void UEnemyClass::Init(FEnemyStruct *enemyStructPointerParam, UMyGameInstance *myGameInstance, uint8 battleInstancePosition)
{
  this->EnemyStructPointer = enemyStructPointerParam;

  this->XpDrop = enemyStructPointerParam->XpDrop;

  for (FString moveset : enemyStructPointerParam->Movesets)
  {
    TArray<FString> parsedMoveset;

    TArray<AttackPatern> auxArray;

    moveset.ParseIntoArray(parsedMoveset, TEXT(","), true);

    for (FString move : parsedMoveset)
    {
      FString moveType = move.Mid(0, 1);

      if (moveType == "W")
      {
        auxArray.Emplace(AttackPatern(WEAK_ATTACK));
      }
      else if (moveType == "M")
      {
        auxArray.Emplace(AttackPatern(MEDIUM_ATTACK));
      }
      else if (moveType == "H")
      {
        auxArray.Emplace(AttackPatern(HEAVY_ATTACK));
      }
      else if (moveType == "S")
      {
        FString spellPosition = move.Mid(1, 1);

        uint8 spellPositionInt = StringToBytes(spellPosition, &spellPositionInt, 8);

        auxArray.Emplace(AttackPatern(CAST_SPELL_MOVESET, spellPositionInt));
      }
    }

    this->Movesets.Emplace(auxArray);
  }

  if (battleInstancePosition > 0)
  {
    this->Position = battleInstancePosition;

    this->PositionForEnemyInBattle = battleInstancePosition;
  }

  this->UCombatActorClass::init(this->EnemyStructPointer, myGameInstance);
}

UEnemyClass::UEnemyClass() {}