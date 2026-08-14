// Fill out your copyright notice in the Description page of Project Settings.


#include "BYGameMode.h"
#include "BYPlayerController.h"
#include "BYGameState.h"

ABYGameMode::ABYGameMode()
{
	PlayerControllerClass = ABYPlayerController::StaticClass();
	GameStateClass = ABYGameState::StaticClass();
}