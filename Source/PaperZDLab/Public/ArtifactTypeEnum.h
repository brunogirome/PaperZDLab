#pragma once

#include "CoreMinimal.h"
#include "ArtifactTypeEnum.generated.h"

UENUM(BlueprintType)
enum ArtifactTypeEnum
{
  NOT_ARTIFACT,
  ARTIFACT_COMPLETE,
  ARTIFACT_COMPONENT,
  BOOTS
};