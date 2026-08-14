// BYResultWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BYResultWidget.generated.h"

UCLASS()
class BBANGYA_API UBYResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Button")
	void Return_OnClicked();
};
