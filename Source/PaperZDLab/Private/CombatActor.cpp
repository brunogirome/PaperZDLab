// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatActor.h"

#include "CombatActorStruct.h"
#include "SpellClass.h"
#include "ItemClass.h"
#include "ActiveBuffStruct.h"

#include "MyGameInstance.h"

void ACombatActor::initialize(FCombatActorStruct *combatActorStruct)
{
    this->CombatActorStructPointer = combatActorStruct;

    this->Name = this->CombatActorStructPointer->Name;

    this->Description = this->CombatActorStructPointer->Description;

    this->TypeOfActor = this->CombatActorStructPointer->TypeOfActor;

    this->CombatType = this->CombatActorStructPointer->CombatType;

    this->Element = this->CombatActorStructPointer->Element;

    this->CalculateStats();

    this->HpCurrent = this->Hp;

    this->ManaCurrent = this->Mana;

    this->StaminaCurrent = this->Stamina;

    int32 amountOfSpells = this->CombatActorStructPointer->SpellsName.Num();

    if (amountOfSpells == 0)
    {
        return;
    }

    for (uint8 i = 0; i < amountOfSpells; i++)
    {
        FName spellName = this->CombatActorStructPointer->SpellsName[i];

        FSpellStruct *spellStruct = this->gameInstance->SpellsDataTable->FindRow<FSpellStruct>(spellName, "", true);

        USpellClass *spellInstance = NewObject<USpellClass>(USpellClass::StaticClass());

        spellInstance->Init(spellStruct, i);

        this->Spells.Emplace(spellInstance);
    }

    this->ASpawnnableActor::initialize(FName(this->Name));
}

void ACombatActor::CalculateStats()
{
    auto getEquipamentStats = [&](BuffTypeEnum itemBuff)
    {
        int flatSum = 0;

        float percentageSum = 0;

        for (UItemClass *equipament : this->Equipaments)
        {
            switch (itemBuff)
            {
            case STRENGTH_BUFF:
                flatSum += equipament->StrengthFlatBonus;

                percentageSum += equipament->StrengthPercentageBonus;
                break;
            case AGILITY_BUFF:
                flatSum += equipament->AgilityFlatBonus;

                percentageSum += equipament->AgilityPercentageBonus;
                break;
            case INTELIGENCE_BUFF:
                flatSum += equipament->InteligenceFlatBonus;

                percentageSum += equipament->InteligencePercentageBonus;
                break;
            case PHYSICAL_DAMAGE_BUFF:
                flatSum += equipament->PhysicalDamageFlatBonus;

                percentageSum += equipament->PhysicalDamagePercentageBonus;
                break;
            case MAGIC_DAMAGE_BUFF:
                flatSum += equipament->MagicDamageFlatBonus;

                percentageSum += equipament->MagicDamagePercentageBonus;
                break;
            case PHYSICAL_DEFENSE_BUFF:
                flatSum += equipament->PhysicalDefenseFlatBonus;

                percentageSum += equipament->PhysicalDefensePercentageBonus;
                break;
            case MAGIC_DEFENSE_BUFF:
                flatSum += equipament->MagicDefenseFlatBonus;

                percentageSum += equipament->MagicDefensePercentageBonus;
                break;
            case HP_BUFF:
                flatSum += equipament->HpFlatBonus;

                percentageSum += equipament->HpPercentageBonus;
                break;
            case MANA_BUFF:
                flatSum += equipament->ManaFlatBonus;

                percentageSum += equipament->ManaPercentageBonus;
                break;
            case SPEED_BUFF:
                flatSum += equipament->SpeedFlatBonus;

                percentageSum += equipament->SpeedPercentageBonus;
                break;
            case STAMINA_BUFF:
                flatSum += equipament->StaminaFlatBonus;

                percentageSum += equipament->StaminaPercentageBonus;
                break;
            case EVASION_BUFF:
                flatSum += equipament->EvasionFlatBonus;

                percentageSum += equipament->EvasionPercentageBonus;
                break;
            default:
                break;
            }
        }

        percentageSum = percentageSum == 0 ? 1 : percentageSum;

        return FEquipamentBuffStruct(flatSum, percentageSum);
    };

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

        FEquipamentBuffStruct equipamentStats = getEquipamentStats(buffType);

        int flatStats = equipamentStats.FlatBonus;

        float percentageStats = equipamentStats.PercentageBonus;

        return (int32)round(((attributeValue * buffValue) + flatStats) * percentageStats);
    };

    auto compositeAttributeCalculation = [&](int32 baseValue, float multiplier, int32 combatTypeValue, TEnumAsByte<CombatTypeEnum> combatTypeBonus, BuffTypeEnum buffType = NOT_BUFF)
    {
        const int32 typeBonus = this->CombatType == combatTypeBonus ? 2 : 1;

        float buffValue = buffType == NOT_BUFF ? 1 : buffFinder(buffType);

        float combatTypeBonusValue = multiplier * combatTypeValue * typeBonus;

        FEquipamentBuffStruct equipamentStats = getEquipamentStats(buffType);

        int flatStats = equipamentStats.FlatBonus;

        float percentageStats = equipamentStats.PercentageBonus;

        return (int32)round((((baseValue + combatTypeBonusValue) * buffValue) + flatStats) * percentageStats);
    };

    this->Strength = basicAttributeCalculation(this->CombatActorStructPointer->StrengthBase, STRENGTH_BUFF);

    this->Inteligence = basicAttributeCalculation(this->CombatActorStructPointer->InteligenceBase, INTELIGENCE_BUFF);

    this->Agility = basicAttributeCalculation(this->CombatActorStructPointer->AgilityBase, AGILITY_BUFF);

    this->Hp = compositeAttributeCalculation(this->CombatActorStructPointer->HpBase, this->HP_BONUS, this->Strength, STRENGTH, HP_BUFF);

    this->Mana = compositeAttributeCalculation(this->CombatActorStructPointer->ManaBase, this->MANA_BONUS, this->Inteligence, INTELIGENCE), MANA_BUFF;

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

bool ACombatActor::IsDead()
{
    return this->HpCurrent <= 0;
}

bool ACombatActor::IsOutOfStamina()
{
    return this->StaminaCurrent <= 0;
}

void ACombatActor::HealHp(int32 amount)
{
    this->HpCurrent = FMath::Clamp(amount + this->HpCurrent, 0, this->Hp);
}

void ACombatActor::TakeDamage(int32 amount)
{
    int32 damageTaken = amount > this->HpCurrent ? this->HpCurrent : amount;

    this->HpCurrent -= damageTaken;
}

void ACombatActor::ReduceStamina(uint8 amount)
{
    this->StaminaCurrent -= amount;
}

void ACombatActor::HealStamina(uint8 amount, bool full)
{
    uint8 amountHealed = full ? this->Stamina : amount;

    this->StaminaCurrent += FMath::Clamp(amount, 0, amountHealed);
}

void ACombatActor::UseMana(int32 amount)
{
    int32 amountSpent = FMath::Clamp(amount, 0, this->Mana);

    this->ManaCurrent -= amountSpent;
}

void ACombatActor::AddBuff(USpellClass *buffSpell)
{
    this->ActiveBuffs.Emplace(FActiveBuffStruct(buffSpell));
}

void ACombatActor::RemoveBuff(uint8 position)
{
    this->ActiveBuffs.RemoveAt(position);
}

ACombatActor::ACombatActor()
{
    this->IsDefending = false;

    this->PositionForEnemyInBattle = 0;
}