// BYMenuWidget.cpp

#include "BYMenuWidget.h"
#include "BYGameState.h"
#include "BYSoundManager.h"
#include "BYTypes.h"

void UBYMenuWidget::Start_OnClicked()
{
	if (ABYGameState* GS = GetWorld()->GetGameState<ABYGameState>())
	{
		GS->SetGameState(EBYGameState::Ingame);
	}

	if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
	{
		SM->PlaySound2D(EBYSFXType::Button);
	}
}