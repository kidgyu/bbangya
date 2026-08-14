// BYMenuWidget.cpp

#include "BYMenuWidget.h"
#include "BYGameState.h"
#include "BYTypes.h"

void UBYMenuWidget::Start_OnClicked()
{
	if (ABYGameState* GS = GetWorld()->GetGameState<ABYGameState>())
	{
		GS->SetGameState(EBYGameState::Ingame);
	}
}