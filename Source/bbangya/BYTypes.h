// BYTypes.h

#pragma once

#include "CoreMinimal.h"
#include "BYTypes.generated.h"

UENUM(BlueprintType)
enum class EBYGameState : uint8
{
	Menu,
	Ingame,
	Result
};

UENUM(BlueprintType)
enum class EBYActorType : uint8
{
	Enemy1,
	Enemy2,
	Enemy3,
	Enemy4,
	Enemy5,

	Bullet,
	Effect_Hit,
	Effect_Die,

	MAX
};

UENUM(BlueprintType)
enum class EBYBGMType : uint8
{
	None,
	Menu,
	Ingame,
	Result
};

UENUM(BlueprintType)
enum class EBYSFXType : uint8
{
	None,
	Shot,
	Die,

	NextLevel,

	GameOver_Voice,
	GameOver_BGM
};