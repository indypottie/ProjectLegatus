#pragma once

#include "RTSSelectionTypes.generated.h"

UENUM(BlueprintType)
enum class ERTSSelectionMode : uint8
{
	Replace		UMETA(DisplayName = "Replace"),
	Add         UMETA(DisplayName = "Add"),
	Toggle      UMETA(DisplayName = "Toggle")
};