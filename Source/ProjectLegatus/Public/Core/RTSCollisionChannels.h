#pragma once

#include "Engine/EngineTypes.h"

namespace RTSCollisionChannels
{
	constexpr ECollisionChannel UnitSelection		= ECC_GameTraceChannel1;
	constexpr ECollisionChannel GroundSelection		= ECC_GameTraceChannel2;
	constexpr ECollisionChannel BuildingPlacement	= ECC_GameTraceChannel3;
}
