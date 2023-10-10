#pragma once

#include "CombatTypeEnum.h"
#include "ElementEnum.h"
#include "TypeOfActorEnum.h"

#include "CombatActorStruct.generated.h"

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

	FCombatActorStruct(FCombatActorStruct *FCombatActorStructPointer);
};