// BYTypes.h

#pragma once

#include "CoreMinimal.h"
#include "BYTypes.generated.h"

UENUM(BlueprintType)
enum class EBYGameState : uint8
{
	Menu,
	Ingame,
	Dying,
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

	Bomb,
	Bullet,

	Effect_Hit,
	Effect_Die,
	Effect_Explosion,

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
	PlayerHurt,

	NextLevel,
	Explode,
	Throw,

	GameOver_Voice,
	GameOver_BGM,

	Button
};