// BYResultWidget.cpp

#include "BYResultWidget.h"
#include "BYGameState.h"
#include "BYTypes.h"

void UBYResultWidget::Return_OnClicked()
{
	if (ABYGameState* GS = GetWorld()->GetGameState<ABYGameState>())
	{
		GS->SetGameState(EBYGameState::Menu);
	}
}
