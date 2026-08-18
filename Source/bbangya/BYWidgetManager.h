// BYWidgetManager.h

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BYWidgetManager.generated.h"

enum class EBYGameState : uint8;
class UBYMenuWidget;
class UBYIngameWidget;
class UBYResultWidget;

UCLASS()
class BBANGYA_API UBYWidgetManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void SetWidgetType(EBYGameState InGameState);

	// Ingame
	void Ingame_SetGameLevel(int32 InLevel);
	void Ingame_SetPlayerHp(int32 InPlayerHp);
	void Ingame_SetKillCount(uint64 InCount);
	void Ingame_SetExpRatio(float InRatio);
	void Ingame_SetPlayerAngle(float InCurrentAngle);
	void Ingame_SetPlayerAngleRange(float InMin, float InMax);

	template <typename T>
	T* CreateUIWidget(const FString& path);

private:
	UPROPERTY()
	TObjectPtr<UBYMenuWidget> CachedMenuWidget;

	UPROPERTY()
	TObjectPtr<UBYIngameWidget> CachedIngameWidget;

	UPROPERTY()
	TObjectPtr<UBYResultWidget> CachedResultWidget;
};

template <typename T>
T* UBYWidgetManager::CreateUIWidget(const FString& path)
{
	FSoftClassPath WidgetClassPath = FSoftClassPath(path);
	UClass* WidgetClass = Cast<UClass>(WidgetClassPath.TryLoad());

	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetClass is null"));
		return nullptr;
	}

	T* Widget = CreateWidget<T>(GetWorld(), WidgetClass);
	if (IsValid(Widget))
	{
		Widget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("failed create widget path : %s"), *path);
	}

	return Widget;
}