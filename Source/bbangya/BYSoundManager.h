// BYSoundManager.h

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BYSoundSettings.h"
#include "BYSoundManager.generated.h"

enum class EBYBGMType : uint8;
enum class EBYSFXType : uint8;

class USoundBase;
class UAudioComponent;

UCLASS()
class BBANGYA_API UBYSoundManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable, Category = "SoundManager|BGM")
	void PlayBGM(EBYBGMType BGMType, float FadeInTime = 1.f);

	UFUNCTION(BlueprintCallable, Category = "SoundManager|BGM")
	void StopBGM(float FadeOutTime = 0.f);

	UFUNCTION(BlueprintCallable, Category = "SoundManager|SFX")
	void PlaySound2D(EBYSFXType SFXType, float VolumeMultiplier = 1.f);

	UFUNCTION(BlueprintCallable, Category = "SoundManager|SFX")
	bool IsPlayingSound2D(EBYSFXType SFXType);

private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> CurrentBGMComponent;

	UPROPERTY()
	TMap<EBYSFXType, TObjectPtr<USoundBase>> LoadedSFXMap;

	UPROPERTY()
	TMap<EBYSFXType, TWeakObjectPtr<UAudioComponent>> ActiveSFXCompoents;

	TMap<EBYSFXType, float> LastPlayTimeMap;
};
