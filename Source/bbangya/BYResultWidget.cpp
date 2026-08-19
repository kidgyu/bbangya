// BYResultWidget.cpp

#include "BYResultWidget.h"
#include "BYGameState.h"
#include "BYSoundManager.h"
#include "BYTypes.h"

void UBYResultWidget::Return_OnClicked()
{
	if (ABYGameState* GS = GetWorld()->GetGameState<ABYGameState>())
	{
		GS->SetGameState(EBYGameState::Menu);
	}

	if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
	{
		SM->PlaySound2D(EBYSFXType::Button);
	}
}
