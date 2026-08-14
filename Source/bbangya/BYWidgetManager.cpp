// BYWidgetManager.cpp

#include "BYWidgetManager.h"
#include "BYMenuWidget.h"
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

	if (IsValid(CachedResultWidget))
		CachedResultWidget->RemoveFromParent();

	CachedMenuWidget = nullptr;
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

	if (!IsValid(CachedResultWidget))
	{
		CachedResultWidget = CreateUIWidget<UBYResultWidget>(TEXT("/Game/UI/BP_BYResultWidget.BP_BYResultWidget_C"));
		CachedResultWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBYWidgetManager::SetWidgetType(EBYGameState InGameState)
{
	CachedMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	CachedResultWidget->SetVisibility(ESlateVisibility::Collapsed);

	switch (InGameState)
	{
	case EBYGameState::Menu: CachedMenuWidget->SetVisibility(ESlateVisibility::Visible); break;
	case EBYGameState::Ingame: break;
	case EBYGameState::Result: CachedResultWidget->SetVisibility(ESlateVisibility::Visible); break;
	}
}