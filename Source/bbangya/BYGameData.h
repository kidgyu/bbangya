// BYGameData.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BYTypes.h"
#include "BYGameData.generated.h"

class ABYActor;

UCLASS(Config=Game, defaultconfig)
class BBANGYA_API UBYGameData : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UBYGameData();
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Actor")
	TMap<EBYActorType, TSoftClassPtr<ABYActor>> ActorClassMap;
};
