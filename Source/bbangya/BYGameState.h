// BYGameState.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BYGameState.generated.h"

enum class EBYGameState : uint8;

UCLASS()
class BBANGYA_API ABYGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ABYGameState();

	EBYGameState GetCurrentGameState() { return GameState; }
	void SetGameState(EBYGameState InGameState);
	void SpawnEnemyInFanShape();
	void OnEnemyDie(int32 InEnemyLevel);
	void SetGameLevelSetting(int32 InLevel);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void OnAllActorsBeginPlayCompleted();

private:
	void StartPlay();
	void PlayerDying();
	void EndGame();

private:
	EBYGameState GameState;

	// GameLevelSetting - Level
	int32 CurrentGameLevel = 1;
	int32 NextLevelKillCount = 0;
	int32 CurrentKillCount = 0;
	uint64 TotalKillCount = 0;

	// GameLevelSetting - Bullet
	int32 BulletCount;
	float BulletSpeed;
	float BulletSpreadAngle;

	// GameLevelSetting - Player
	float FireAttackTime;
	float FireDamage;

	// GameLevelSetting - Enemy
	int32 EnemySpawnCount;
	float EnemySpawnTime;
	float EnemyHP;
	float EnemyDamage;
	float EnemySpawnDistance_Min;
	float EnemySpawnDistance_Max;
	float EnemySpawnAngle_Min;
	float EnemySpawnAngle_Max;
	float EnemySpeedMin;
	float EnemySpeedMax;

	// Game State
	float EnemySpawnElapsedTime = 0.f;
	float EnemyPosition_Z = 80.f;
};