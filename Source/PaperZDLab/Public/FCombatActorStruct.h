#pragma once

#include "CombatTypeEnum.h"
#include "ElementEnum.h"
#include "TypeOfActorEnum.h"

#include "FCombatActorStruct.generated.h"

USTRUCT(BlueprintType)
struct FCombatActorStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 Id;

	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString Description;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<TypeOfActorEnum> TypeOfActor;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<CombatTypeEnum> CombatType;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ElementEnum> Element;

	UPROPERTY(BlueprintReadOnly)
	int32 StrengthBase;

	UPROPERTY(BlueprintReadOnly)
	int32 AgilityBase;

	UPROPERTY(BlueprintReadOnly)
	int32 InteligenceBase;

	UPROPERTY(BlueprintReadOnly)
	int32 PhysicalDamageBase;

	UPROPERTY(BlueprintReadOnly)
	int32 MagicDamageBase;

	UPROPERTY(BlueprintReadOnly)
	int32 PhysicalDefenseBase;

	UPROPERTY(BlueprintReadOnly)
	int32 MagicDefenseBase;

	UPROPERTY(BlueprintReadOnly)
	int32 HpBase;

	UPROPERTY(BlueprintReadOnly)
	int32 ManaBase;

	UPROPERTY(BlueprintReadOnly)
	int32 SpeedBase;

	UPROPERTY(BlueprintReadOnly)
	int32 EvasionBase;

	UPROPERTY(BlueprintReadOnly)
	int32 StaminaBase;

	FCombatActorStruct();

	FCombatActorStruct(int32 id, FString name, FString description, TEnumAsByte<TypeOfActorEnum> typeOfActor, TEnumAsByte<CombatTypeEnum> combatType, TEnumAsByte<ElementEnum> element, int32 strengthBase, int32 agilityBase, int32 inteligenceBase, int32 physicalDamageBase, int32 magicDamageBase, int32 physicalDefenseBase, int32 magicDefenseBase, int32 hpBase, int32 manaBase, int32 speedBase, int32 evasionBase, int32 staminaBase);
};