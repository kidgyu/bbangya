// BYPlayerController.cpp

#include "BYPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BYGameState.h"
#include "BYActorManager.h"
#include "BYPlayerPawn.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BYWidgetManager.h"
#include "BYTypes.h"

ABYPlayerController::ABYPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObject(TEXT("/Game/Input/IMC_Default.IMC_Default"));
	if (IMCObject.Succeeded())
	{
		DefaultMappingContext = IMCObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAObject(TEXT("/Game/Input/IA_DragLook.IA_DragLook"));
	if (IAObject.Succeeded())
	{
		DragLookAction = IAObject.Object;
	}
}

void ABYPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 컨트롤러에서 매핑 컨텍스트 추가
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableTouchEvents = true;
	}

	GameState = GetWorld()->GetGameState<ABYGameState>();
}

void ABYPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (GameState)
	{
		if (GameState->GetCurrentGameState() == EBYGameState::Menu
			|| GameState->GetCurrentGameState() == EBYGameState::Result)
			return;
	}
	
	// EnhancedInputComponent로 캐스팅 후 액션 바인딩
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 터치/드래그가 유지되는 동안(Triggered) LookRotation 함수 호출
		if (DragLookAction)
		{
			EnhancedInputComponent->BindAction(DragLookAction, ETriggerEvent::Triggered, this, &ABYPlayerController::LookRotation);
		}
	}
}

void ABYPlayerController::LookRotation(const FInputActionValue& Value)
{
	if (IsValid(GameState))
	{
		if (GameState->GetCurrentGameState() != EBYGameState::Ingame)
			return;
	}

	float CalculatedYawInput = 0.f;

	bool bIsCurrentlyTouching = false;
	float CurrentTouchX = 0.f;
	float CurrentTouchY = 0.f;
	GetInputTouchState(ETouchIndex::Touch1, CurrentTouchX, CurrentTouchY, bIsCurrentlyTouching);

	if (bIsCurrentlyTouching)
	{
		FVector2D CurrentTouchPos(CurrentTouchX, CurrentTouchY);
		if (!bIsTouchDragging)
		{
			bIsTouchDragging = true;
			LastTouchPosition = CurrentTouchPos;
		}
		else
		{
			CalculatedYawInput = CurrentTouchPos.X - LastTouchPosition.X;
			LastTouchPosition = CurrentTouchPos;
		}
	}
	else
	{
		bIsTouchDragging = false;
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		CalculatedYawInput = LookAxisVector.X;
	}

	//월드 서브 시스템에서 액터 매니저를 가져오기
	if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
	{
		if (ABYPlayerPawn* PlayerPawn = AM->GetPlayerPawn())
		{
			FRotator CurrentRotation = PlayerPawn->GetActorRotation();
			FRotator DeltaRotation = FRotator(0.f, CalculatedYawInput * RotationSpeed, 0.f);
			FRotator NewRotation = CurrentRotation + DeltaRotation;

			NewRotation.Yaw = FMath::ClampAngle(NewRotation.Yaw, AM->GetPlayerRotationAngleMin(), AM->GetPlayerRotationAngleMax());
			PlayerPawn->SetActorRotation(NewRotation);

			if (UBYWidgetManager* WM = GetWorld()->GetSubsystem<UBYWidgetManager>())
			{
				float CurrentAngle = static_cast<float>(NewRotation.Yaw);
				WM->Ingame_SetPlayerAngle(CurrentAngle);
			}
		}
	}
}