#pragma once

#include "CombatTypeEnum.h"
#include "ElementEnum.h"
#include "TypeOfActorEnum.h"

#include "CombatActor.generated.h"

USTRUCT(BlueprintType)
struct FCombatActor : public FTableRowBase
{
    GENERATED_BODY()
private:
    float HP_MULTIPLIER = 2.5f;
    float MANA_MULTIPLIER = 2.5f;
    float SPEED_MULTIPLIER = 0.5f;
    float EVASION_MULTIPLIER = 0.5f;
    float STAMINA_MULTIPLIER = 0.25f;

    float PHYSICAL_DAMAGE_MULTIPLIER = 1.25f;
    float MAGIC_DAMAGE_MULTIPLIER = 1.8f;

    float PHYSICAL_DEFENSE_MULTIPLIER = 0.5f;
    float MAGIC_DEFENSE_MULTIPLIER = 0.5f;

public:
    // General character data
    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Id"))
    int32 Id;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Name"))
    FString Name;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "TypeOfActor"))
    TEnumAsByte<TypeOfActorEnum> TypeOfActor;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "CombatType"))
    TEnumAsByte<CombatTypeEnum> CombatType;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Element"))
    TEnumAsByte<ElementEnum> Element;

    // Combat Type Status
    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Strength"))
    int32 Strength;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Agility"))
    int32 Agility;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Inteligence"))
    int32 Inteligence;

    // Base Combat Status
    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "HpBase"))
    int32 HpBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "ManaBase"))
    int32 ManaBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "SpeedBase"))
    int32 SpeedBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "EvasionBase"))
    int32 EvasionBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "StaminaBase"))
    int32 StaminaBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "PhysicalDamageBase"))
    int32 PhysicalDamageBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "MagicDamageBase"))
    int32 MagicDamageBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "PhysicalDefenseBase"))
    int32 PhysicalDefenseBase;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "MagicDefenseBase"))
    int32 MagicDefenseBase;

    // Effective Combat Status
    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "HpTotal"))
    int32 HpTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "ManaTotal"))
    int32 ManaTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "SpeedTotal"))
    int32 SpeedTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "EvasionTotal"))
    int32 EvasionTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "StaminaTotal"))
    int32 StaminaTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "MeelePowerTotal"))
    int32 MeelePowerTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "MagicPowerTotal"))
    int32 MagicPowerTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "MeeleDefenseTotal"))
    int32 MeeleDefenseTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "MagicDefenseTotal"))
    int32 MagicDefenseTotal;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "HpCurrent"))
    int32 HpCurrent;

    UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "ManaCurrent"))
    int32 ManaCurrent;

    FCombatActor();

    FCombatActor(int32 id, FString name, TEnumAsByte<TypeOfActorEnum> typeOfActor, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strength, int32 agility, int32 inteligence, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase);
};
