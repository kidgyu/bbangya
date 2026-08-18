// BYIngameWidget.cpp

#include "BYIngameWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/RadialSlider.h"

void UBYIngameWidget::SetGameLevel(int32 InLevel)
{
	FText Text = FText::FromString(FString::Printf(TEXT("%d"), InLevel));
	Text_Level->SetText(Text);
}

void UBYIngameWidget::SetPlayerHp(int32 InPlayerHp)
{
	FText Text = FText::FromString(FString::Printf(TEXT("%d"), InPlayerHp));
	Text_Hp->SetText(Text);
}

void UBYIngameWidget::SetKillCount(uint64 InCount)
{
	FText Text = FText::FromString(FString::Printf(TEXT("%llu"), InCount));
	Text_KillCount->SetText(Text);
}

void UBYIngameWidget::SetExpRatio(float InRatio)
{
	ProgressBar_EXP->SetPercent(InRatio);
}

void UBYIngameWidget::SetPlayerAngle(float InCurrentAngle)
{	
	float ConvertAngle = InCurrentAngle + 180.f - Slider_PlayerAngle->SliderHandleStartAngle;
	float ConvertMaxAngle = Slider_PlayerAngle->SliderHandleEndAngle - Slider_PlayerAngle->SliderHandleStartAngle;
	float FinalAngle = FMath::Clamp(ConvertAngle, 0.f, ConvertMaxAngle);

	Slider_PlayerAngle->SetValue(FinalAngle / ConvertMaxAngle);
}

void UBYIngameWidget::SetPlayerAngleRange(float InMin, float InMax)
{
	Slider_PlayerAngle->SetSliderHandleStartAngle(InMin);
	Slider_PlayerAngle->SetSliderHandleEndAngle(InMax);
}
