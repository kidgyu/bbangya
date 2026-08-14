// BYPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "BYPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABYGameState;

UCLASS()
class BBANGYA_API ABYPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABYPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext; // 입력 할당

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> DragLookAction; // 좌우 드래그 액션

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float RotationSpeed = 2.f;

	UPROPERTY()
	TObjectPtr<ABYGameState> GameState;

protected:
	void LookRotation(const FInputActionValue& Value);
};
