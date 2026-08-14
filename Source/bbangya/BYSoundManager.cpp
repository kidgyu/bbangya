// BYSoundManager.cpp

#include "BYSoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

void UBYSoundManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentBGMComponent = nullptr;
}

void UBYSoundManager::Deinitialize()
{
	StopBGM(0.f);

	LoadedSFXMap.Empty();
	ActiveSFXCompoents.Empty();

	Super::Deinitialize();
}

void UBYSoundManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	const UBYSoundSettings* SoundSettings = GetDefault<UBYSoundSettings>();
	if (!SoundSettings)
		return;

	for (const auto& Pair : SoundSettings->SFXList)
	{
		EBYSFXType Type = Pair.Key;
		const TSoftObjectPtr<USoundBase>& SoftPtr = Pair.Value;
		if (USoundBase* LoadedSFX = SoftPtr.LoadSynchronous())
		{
			LoadedSFXMap.Add(Type, LoadedSFX);
		}
	}
}

void UBYSoundManager::PlayBGM(EBYBGMType BGMType, float FadeInTime)
{
	if (BGMType == EBYBGMType::None)
		return;

	const UBYSoundSettings* SoundSettings = GetDefault<UBYSoundSettings>();
	if (const TSoftObjectPtr<USoundBase>* FoundSoundPtr = SoundSettings->BGMList.Find(BGMType))
	{
		if (USoundBase* LoadedBGM = FoundSoundPtr->LoadSynchronous())
		{
			if (UWorld* World = GetWorld())
			{
				CurrentBGMComponent = UGameplayStatics::CreateSound2D(
					World,
					LoadedBGM,
					1.f,
					1.f,
					0.f,
					nullptr,
					true,
					false
				);

				if (CurrentBGMComponent)
				{
					CurrentBGMComponent->FadeIn(FadeInTime);
				}
			}
		}
	}
}

void UBYSoundManager::StopBGM(float FadeOutTime)
{
	if (CurrentBGMComponent && CurrentBGMComponent->IsPlaying())
	{
		if (FadeOutTime > 0.f)
		{
			CurrentBGMComponent->FadeOut(FadeOutTime, 0.f);
		}
		else
		{
			CurrentBGMComponent->Stop();
		}
	}

	CurrentBGMComponent = nullptr;
}

void UBYSoundManager::PlaySound2D(EBYSFXType SFXType, float VolumeMultiplier)
{
	if (SFXType == EBYSFXType::None)
		return;

	/*if (IsPlayingSound2D(SFXType))
		return;*/

	if (TObjectPtr<USoundBase>* FoundSound = LoadedSFXMap.Find(SFXType))
	{
		if (*FoundSound)
		{
			UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), *FoundSound, VolumeMultiplier);
			if (AudioComp)
			{
				if (ActiveSFXCompoents.Contains(SFXType))
				{
					ActiveSFXCompoents.Remove(SFXType);
				}

				ActiveSFXCompoents.Add(SFXType, AudioComp);
			}
		}
	}
}

bool UBYSoundManager::IsPlayingSound2D(EBYSFXType SFXType)
{
	if (!LoadedSFXMap.Contains(SFXType))
		return false;

	if (TWeakObjectPtr<UAudioComponent>* ActiveCompPtr = ActiveSFXCompoents.Find(SFXType))
	{
		if (ActiveCompPtr->IsValid())
		{
			return (*ActiveCompPtr)->IsPlaying();
		}
		else
		{
			if (ActiveSFXCompoents.Contains(SFXType))
			{
				ActiveSFXCompoents.Remove(SFXType);
			}
		}
	}

	return false;
}