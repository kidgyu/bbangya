// BYWidgetManager.cpp

#include "BYWidgetManager.h"
#include "BYMenuWidget.h"
#include "BYIngameWidget.h"
#include "BYResultWidget.h"
#include "BYTypes.h"

void UBYWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBYWidgetManager::Deinitialize()
{
	if (IsValid(CachedMenuWidget))
		CachedMenuWidget->RemoveFromParent();

	if (IsValid(CachedIngameWidget))
		CachedIngameWidget->RemoveFromParent();

	if (IsValid(CachedResultWidget))
		CachedResultWidget->RemoveFromParent();

	CachedMenuWidget = nullptr;
	CachedIngameWidget = nullptr;
	CachedResultWidget = nullptr;

	Super::Deinitialize();
}

void UBYWidgetManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (!IsValid(CachedMenuWidget))
	{
		CachedMenuWidget = CreateUIWidget<UBYMenuWidget>(TEXT("/Game/UI/BP_BYMenuWidget.BP_BYMenuWidget_C"));
		CachedMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (!IsValid(CachedIngameWidget))
	{
		CachedIngameWidget = CreateUIWidget<UBYIngameWidget>(TEXT("/Game/UI/BP_BYIngameWidget.BP_BYIngameWidget_C"));
		CachedIngameWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (!IsValid(CachedResultWidget))
	{
		CachedResultWidget = CreateUIWidget<UBYResultWidget>(TEXT("/Game/UI/BP_BYResultWidget.BP_BYResultWidget_C"));
		CachedResultWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBYWidgetManager::SetWidgetType(EBYGameState InGameState)
{
	CachedMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	CachedIngameWidget->SetVisibility(ESlateVisibility::Collapsed);
	CachedResultWidget->SetVisibility(ESlateVisibility::Collapsed);

	switch (InGameState)
	{
	case EBYGameState::Menu: CachedMenuWidget->SetVisibility(ESlateVisibility::Visible); break;
	case EBYGameState::Ingame: CachedIngameWidget->SetVisibility(ESlateVisibility::Visible); break;
	case EBYGameState::Dying: break;
	case EBYGameState::Result: CachedResultWidget->SetVisibility(ESlateVisibility::Visible); break;
	}
}

void UBYWidgetManager::Ingame_SetGameLevel(int32 InLevel)
{
	if (CachedIngameWidget)
		CachedIngameWidget->SetGameLevel(InLevel);
}

void UBYWidgetManager::Ingame_SetPlayerHp(int32 InPlayerHp)
{
	if (CachedIngameWidget)
		CachedIngameWidget->SetPlayerHp(InPlayerHp);
}

void UBYWidgetManager::Ingame_SetKillCount(uint64 InCount)
{
	if (CachedIngameWidget)
		CachedIngameWidget->SetKillCount(InCount);
}

void UBYWidgetManager::Ingame_SetExpRatio(float InRatio)
{
	if (CachedIngameWidget)
		CachedIngameWidget->SetExpRatio(InRatio);
}

void UBYWidgetManager::Ingame_SetPlayerAngle(float InCurrentAngle)
{
	if (CachedIngameWidget)
		CachedIngameWidget->SetPlayerAngle(InCurrentAngle);
}

void UBYWidgetManager::Ingame_SetPlayerAngleRange(float InMin, float InMax)
{
	if (CachedIngameWidget)
		CachedIngameWidget->SetPlayerAngleRange(InMin, InMax);
}