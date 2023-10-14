#pragma once

#include "CombatTypeEnum.h"
#include "ElementEnum.h"
#include "TypeOfActorEnum.h"

#include "CombatActorStruct.generated.h"

USTRUCT(BlueprintType)
struct FCombatActorStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<TypeOfActorEnum> TypeOfActor;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<CombatTypeEnum> CombatType;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ElementEnum> Element;

	UPROPERTY(EditAnywhere)
	int32 StrengthBase;

	UPROPERTY(EditAnywhere)
	int32 AgilityBase;

	UPROPERTY(EditAnywhere)
	int32 InteligenceBase;

	UPROPERTY(EditAnywhere)
	int32 PhysicalDamageBase;

	UPROPERTY(EditAnywhere)
	int32 MagicDamageBase;

	UPROPERTY(EditAnywhere)
	int32 PhysicalDefenseBase;

	UPROPERTY(EditAnywhere)
	int32 MagicDefenseBase;

	UPROPERTY(EditAnywhere)
	int32 HpBase;

	UPROPERTY(EditAnywhere)
	int32 ManaBase;

	UPROPERTY(EditAnywhere)
	int32 SpeedBase;

	UPROPERTY(EditAnywhere)
	int32 EvasionBase;

	UPROPERTY(EditAnywhere)
	int32 StaminaBase;

	UPROPERTY(EditAnywhere)
	TArray<FName> SpellsName;

	FCombatActorStruct();

	FCombatActorStruct(FCombatActorStruct *FCombatActorStructPointer);
};