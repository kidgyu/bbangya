// BYGameLevelData.cpp

#include "BYGameLevelSettings.h"

UBYGameLevelSettings::UBYGameLevelSettings()
{
	AddGameLevelData(1, // Level
		5,		// Next Level Kill Count
		1,		// Bullet Count
		2000.f,	// Bullet Speed
		0.f,	// BulletSpreadAngle
		0.4f,	// Fire Attack Time
		1.f,	// FireDamage
		1,		// Enemy Spawn Count
		0.5f,	// Enemy Spawn Time
		1.f,	// Enemy HP
		1.f,	// Enemy Damage
		400.f,	// Enemy Spawn Distance_Min
		600.f,	// Enemy Spawn Distance_Max
		-30.f,	// Enemy Spawn Angle_Min
		30.f,	// Enemy Spawn Angle_Max
		30.f,	// Enemy Speed Min
		50.f	// Enemy Speed Max
	);	

	AddGameLevelData(2,
		20,		// Next Level Kill Count
		2,		// BulletCount
		2400.f,	// BulletSpeed
		30.f,	// BulletSpreadAngle
		0.34f,	// Fire Attack Time
		1.f,	// FireDamage
		1,		// Enemy Spawn Count
		0.34f,	// Enemy Spawn Time
		1.f,	// Enemy HP
		2.f,	// Enemy Damage
		500.f,	// EnemySpawnDistance_Min
		700.f,	// EnemySpawnDistance_Max
		-40.f,	// EnemySpawnAngle_Min
		40.f,	// EnemySpawnAngle_Max
		40.f,	// EnemySpeedMin
		70.f	// EnemySpeedMax
	);	

	AddGameLevelData(3,
		60,		// Next Level Kill Count
		3,		// BulletCount
		2600.f,	// BulletSpeed
		20.f,	// BulletSpreadAngle
		0.3f,	// Fire Attack Time
		1.f,	// FireDamage
		2,		// Enemy Spawn Count
		0.28f,	// Enemy Spawn Time
		2.f,	// Enemy HP
		4.f,	// Enemy Damage
		600.f,	// EnemySpawnDistance_Min
		900.f,	// EnemySpawnDistance_Max
		-50.f,	// EnemySpawnAngle_Min
		50.f,	// EnemySpawnAngle_Max
		60.f,	// EnemySpeedMin
		80.f	// EnemySpeedMax
	);	

	AddGameLevelData(4,
		100,	// Next Level Kill Count
		4,		// BulletCount
		2800.f,	// BulletSpeed
		15.f,	// BulletSpreadAngle
		0.24f,	// Fire Attack Time
		2.f,	// FireDamage
		2,		// Enemy Spawn Count
		0.24f,	// Enemy Spawn Time
		4.f,	// Enemy HP
		6.f,	// Enemy Damage
		700.f,	// EnemySpawnDistance_Min
		1000.f,	// EnemySpawnDistance_Max
		-60.f,	// EnemySpawnAngle_Min
		60.f,	// EnemySpawnAngle_Max
		70.f,	// EnemySpeedMin
		100.f	// EnemySpeedMax
	);	

	AddGameLevelData(5,
		200,	// Next Level Kill Count
		5,		// BulletCount
		3000.f,	// BulletSpeed
		10.f,	// BulletSpreadAngle
		0.2f,	// Fire Attack Time
		4.f,	// FireDamage
		3,		// Enemy Spawn Count
		0.2f,	// Enemy Spawn Time
		8.f,	// Enemy HP
		8.f,	// Enemy Damage
		800.f,	// EnemySpawnDistance_Min
		1200.f,	// EnemySpawnDistance_Max
		-70.f,	// EnemySpawnAngle_Min
		70.f,	// EnemySpawnAngle_Max
		100.f,	// EnemySpeedMin
		140.f	// EnemySpeedMax
	);	

	AddGameLevelData(6,
		400,	// Next Level Kill Count
		6,		// BulletCount
		3400.f,	// BulletSpeed
		10.f,	// BulletSpreadAngle
		0.16f,	// Fire Attack Time
		6.f,	// FireDamage
		3,		// Enemy Spawn Count
		0.18f,	// Enemy Spawn Time
		12.f,	// Enemy HP
		8.f,	// Enemy Damage
		800.f,	// EnemySpawnDistance_Min
		1400.f,	// EnemySpawnDistance_Max
		-70.f,	// EnemySpawnAngle_Min
		70.f,	// EnemySpawnAngle_Max
		140.f,	// EnemySpeedMin
		200.f	// EnemySpeedMax
	);

	AddGameLevelData(7,
		0,		// Next Level Kill Count
		8,		// BulletCount
		3600.f,	// BulletSpeed
		8.f,	// BulletSpreadAngle
		0.12f,	// Fire Attack Time
		6.f,	// FireDamage
		4,		// Enemy Spawn Count
		0.14f,	// Enemy Spawn Time
		12.f,	// Enemy HP
		50.f,	// Enemy Damage
		800.f,	// EnemySpawnDistance_Min
		1400.f,	// EnemySpawnDistance_Max
		-80.f,	// EnemySpawnAngle_Min
		80.f,	// EnemySpawnAngle_Max
		200.f,	// EnemySpeedMin
		240.f	// EnemySpeedMax
	);
}

void UBYGameLevelSettings::AddGameLevelData(int32 InLevel, int32 InNextLevelKillCount, int32 InBulletCount, float InBulletSpeed, float InBulletSpreadAngle, float InFireAttackTime, float InFireDamage, int32 InEnemySpawnCount, float InEnemySpawnTime, float InEnemyHP, float InEnemyDamage, float InEnemySpawnDistance_Min, float InEnemySpawnDistance_Max, float InEnemySpawnAngle_Min, float InEnemySpawnAngle_Max, float InEnemySpeedMin, float InEnemySpeedMax)
{
	FBYGameLevelData LevelSetting;

	LevelSetting.Level					= InLevel;
	LevelSetting.NextLevelKillCount		= InNextLevelKillCount;
	LevelSetting.BulletCount			= InBulletCount;
	LevelSetting.BulletSpeed			= InBulletSpeed;
	LevelSetting.BulletSpreadAngle		= InBulletSpreadAngle;
	LevelSetting.FireAttackTime			= InFireAttackTime;
	LevelSetting.FireDamage				= InFireDamage;
	LevelSetting.EnemySpawnCount		= InEnemySpawnCount;
	LevelSetting.EnemySpawnTime			= InEnemySpawnTime;
	LevelSetting.EnemyHP				= InEnemyHP;
	LevelSetting.EnemyDamage			= InEnemyDamage;
	LevelSetting.EnemySpawnDistance_Min = InEnemySpawnDistance_Min;
	LevelSetting.EnemySpawnDistance_Max	= InEnemySpawnDistance_Max;
	LevelSetting.EnemySpawnAngle_Min	= InEnemySpawnAngle_Min;
	LevelSetting.EnemySpawnAngle_Max	= InEnemySpawnAngle_Max;
	LevelSetting.EnemySpeedMin			= InEnemySpeedMin;
	LevelSetting.EnemySpeedMax			= InEnemySpeedMax;

	GameLevelSettingsMap.Add(InLevel, LevelSetting);
}