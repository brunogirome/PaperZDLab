// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatActorClass.h"

#include "MyGameInstance.h"

void UCombatActorClass::init(FCombatActorStruct *combatActorStructPointer, UMyGameInstance *myGameInstance)
{
    this->gameInstance = myGameInstance;

    this->CombatActorStructPointer = combatActorStructPointer;

    this->Name = combatActorStructPointer->Name;

    this->Description = combatActorStructPointer->Description;

    this->TypeOfActor = combatActorStructPointer->TypeOfActor;

    this->CombatType = combatActorStructPointer->CombatType;

    this->Element = combatActorStructPointer->Element;

    this->CalculateStats();

    this->HpCurrent = this->Hp;

    this->ManaCurrent = this->Mana;

    this->StaminaCurrent = this->Stamina;

    if (combatActorStructPointer->SpellsName.Num() == 0)
    {
        return;
    }

    TArray<FString> spellsArray;

    combatActorStructPointer->SpellsName[0].ToString().ParseIntoArray(spellsArray, TEXT(","), true);

    uint8 index = 0;

    for (FString spellName : spellsArray)
    {
        FSpellStruct *spellStruct = this->gameInstance->SpellsDataTable->FindRow<FSpellStruct>(FName(spellName.TrimStartAndEnd()), "", true);

        USpellClass *spellInstance = NewObject<USpellClass>(USpellClass::StaticClass());

        spellInstance->Init(spellStruct, index);

        this->Spells.Emplace(spellInstance);

        index++;
    }
}

void UCombatActorClass::CalculateStats()
{
    auto buffFinder = [&](BuffTypeEnum buffType)
    {
        float buffAmount = 1;

        for (FActiveBuffStruct buff : this->ActiveBuffs)
        {
            if (buff.SpellPointer->BuffType == buffType)
            {
                buffAmount += buff.SpellPointer->Multiplier;

                break;
            }
        }

        return buffAmount;
    };

    auto basicAttributeCalculation = [&](int32 attributeValue, BuffTypeEnum buffType = NOT_BUFF)
    {
        float buffValue = buffType == NOT_BUFF ? 1 : buffFinder(buffType);

        return (int32)round(attributeValue * buffValue);
    };

    auto compositeAttributeCalculation = [&](int32 baseValue, float multiplier, int32 combatTypeValue, TEnumAsByte<CombatTypeEnum> combatTypeBonus, BuffTypeEnum buffType = NOT_BUFF)
    {
        const int32 typeBonus = this->CombatType == combatTypeBonus ? 2 : 1;

        float buffValue = buffType == NOT_BUFF ? 1 : buffFinder(buffType);

        float combatTypeBonusValue = multiplier * combatTypeValue * typeBonus;

        return (int32)round((baseValue + combatTypeBonusValue) * buffValue);
    };

    this->Strength = basicAttributeCalculation(this->CombatActorStructPointer->StrengthBase, STRENGTH_BUFF);

    this->Inteligence = basicAttributeCalculation(this->CombatActorStructPointer->InteligenceBase, INTELIGENCE_BUFF);

    this->Agility = basicAttributeCalculation(this->CombatActorStructPointer->AgilityBase, AGILITY_BUFF);

    this->Hp = compositeAttributeCalculation(this->CombatActorStructPointer->HpBase, this->HP_BONUS, this->Strength, STRENGTH);

    this->Mana = compositeAttributeCalculation(this->CombatActorStructPointer->ManaBase, this->MANA_BONUS, this->Inteligence, INTELIGENCE);

    this->Speed = compositeAttributeCalculation(this->CombatActorStructPointer->SpeedBase, this->SPEED_BONUS, this->Agility, AGILITY, SPEED_BUFF);

    this->Evasion = compositeAttributeCalculation(this->CombatActorStructPointer->EvasionBase, this->EVASION_BONUS, this->Agility, AGILITY, EVASION_BUFF);

    this->Stamina = compositeAttributeCalculation(this->CombatActorStructPointer->StaminaBase, this->STAMINA_BONUS, this->Agility, AGILITY, STAMINA_BUFF);

    this->PhysicalDamage = compositeAttributeCalculation(this->CombatActorStructPointer->PhysicalDamageBase, this->PHYSICAL_DAMAGE_BONUS, this->Strength, STRENGTH, PHYSICAL_DAMAGE_BUFF);

    this->MagicDamage = compositeAttributeCalculation(this->CombatActorStructPointer->MagicDamageBase, this->MAGIC_DAMAGE_BONUS, this->Inteligence, INTELIGENCE, MAGIC_DAMAGE_BUFF);

    this->PhysicalDefense = compositeAttributeCalculation(this->CombatActorStructPointer->PhysicalDefenseBase, this->PHYSICAL_DEFENSE_BONUS, this->Strength, STRENGTH, PHYSICAL_DEFENSE_BUFF);

    this->MagicDefense = compositeAttributeCalculation(this->CombatActorStructPointer->MagicDefenseBase, this->MAGIC_DEFENSE_BONUS, this->Inteligence, INTELIGENCE, MAGIC_DEFENSE_BUFF);

    auto accuracyCalculation = [&](uint8 strength)
    {
        float bonus = this->CombatType == AGILITY ? 1.05 : 1;

        float calculation = this->gameInstance->ATTACK_STRENGTH_ACCURACY_BASE[strength];

        calculation *= 1 + (this->Agility / 300);

        calculation = FMath::Clamp(calculation, 0, 99.99f);

        return calculation;
    };

    this->WeakAccuracy = accuracyCalculation(0);

    this->MediumAccuracy = accuracyCalculation(1);

    this->StrongAccuracy = accuracyCalculation(2);
}

bool UCombatActorClass::IsDead()
{
    return this->HpCurrent <= 0;
}

bool UCombatActorClass::IsOutOfStamina()
{
    return this->StaminaCurrent <= 0;
}

void UCombatActorClass::HealHp(int32 amount)
{
    this->HpCurrent = FMath::Clamp(amount + this->HpCurrent, 0, this->Hp);
}

void UCombatActorClass::TakeDamage(int32 amount)
{
    int32 damageTaken = amount > this->HpCurrent ? this->HpCurrent : amount;

    this->HpCurrent -= damageTaken;
}

void UCombatActorClass::ReduceStamina(uint8 amount)
{
    this->StaminaCurrent -= amount;
}

void UCombatActorClass::HealStamina(uint8 amount, bool full)
{
    uint8 amountHealed = full ? this->Stamina : amount;

    this->StaminaCurrent += FMath::Clamp(amount, 0, amountHealed);
}

void UCombatActorClass::UseMana(int32 amount)
{
    int32 amountSpent = FMath::Clamp(amount, 0, this->Mana);

    this->ManaCurrent -= amountSpent;
}

void UCombatActorClass::AddBuff(USpellClass *buffSpell)
{
    this->ActiveBuffs.Emplace(FActiveBuffStruct(buffSpell));
}

void UCombatActorClass::RemoveBuff(uint8 position)
{
    this->ActiveBuffs.RemoveAt(position);
}

UCombatActorClass::UCombatActorClass() {}
