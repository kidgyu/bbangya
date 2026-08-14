// BYSoundSettings.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BYTypes.h"
#include "BYSoundSettings.generated.h"

UCLASS(Config=Game, defaultconfig, meta=(DisplayName="BY Sound Setting"))
class BBANGYA_API UBYSoundSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Audio|BGM")
	TMap<EBYBGMType, TSoftObjectPtr<USoundBase>> BGMList;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Audio|SFX")
	TMap<EBYSFXType, TSoftObjectPtr<USoundBase>> SFXList;
};
