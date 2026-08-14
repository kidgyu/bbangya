// BYGameLevelData.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BYGameLevelSettings.generated.h"

USTRUCT(BlueprintType)
struct FBYGameLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	int32 Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	int32 NextLevelKillCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	int32 BulletCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float BulletSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float BulletSpreadAngle = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float FireAttackTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float FireDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	int32 EnemySpawnCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpawnTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemyHP = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemyDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpawnDistance_Min = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpawnDistance_Max = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpawnAngle_Min = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpawnAngle_Max = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpeedMin = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpeedMax = 0.f;
};

UCLASS(Config=Game, defaultconfig, meta=(DisplayName="BY Level Setting"))
class BBANGYA_API UBYGameLevelSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UBYGameLevelSettings();

private:
	void AddGameLevelData(int32 InLevel, int32 InNextLevelKillCount, int32 InBulletCount, float InBulletSpeed, float InBulletSpreadAngle, float InFireAttackTime, float InFireDamage, int32 InEnemySpawnCount, float InEnemySpawnTime, float InEnemyHP, float InEnemyDamage, float InEnemySpawnDistance_Min, float InEnemySpawnDistance_Max, float InEnemySpawnAngle_Min, float InEnemySpawnAngle_Max, float InEnemySpeedMin, float InEnemySpeedMax);

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Game|Level")
	TMap<int32, FBYGameLevelData> GameLevelSettingsMap;

private:
	int32 StartLevel = 1;
};
