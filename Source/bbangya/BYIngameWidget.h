// BYIngameWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BYIngameWidget.generated.h"

class UTextBlock;
class UProgressBar;
class URadialSlider;

UCLASS()
class BBANGYA_API UBYIngameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnClick_Bomb();
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Level;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Hp;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_KillCount;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Bomb;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_EXP;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URadialSlider> Slider_PlayerAngle;

public:
	void SetGameLevel(int32 InLevel);
	void SetPlayerHp(int32 InPlayerHp);
	void SetKillCount(uint64 InCount);
	void SetExpRatio(float InRatio);
	void SetPlayerAngle(float InCurrentAngle);
	void SetPlayerAngleRange(float InMin, float InMax);
};
