#pragma once

#include "FormationTypes.generated.h"

UENUM(BlueprintType)
enum class EFormationType : uint8
{
	Line,
	Column,
	Square,
	Wedge,
};
