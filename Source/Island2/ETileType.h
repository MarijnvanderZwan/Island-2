#pragma once

#include "GameFramework/Actor.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	Empty,
	Blocking,
	Goal
};
