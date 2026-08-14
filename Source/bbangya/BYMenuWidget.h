// BYMenuWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BYMenuWidget.generated.h"

UCLASS()
class BBANGYA_API UBYMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Button")
	void Start_OnClicked();
};
