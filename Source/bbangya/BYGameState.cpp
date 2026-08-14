// Fill out your copyright notice in the Description page of Project Settings.

#include "BYGameState.h"
#include "BYActorManager.h"
#include "BYPlayerPawn.h"
#include "BYEnemyActor.h"
#include "BYWidgetManager.h"
#include "BYTypes.h"
#include "BYGameLevelSettings.h"
#include "BYSoundManager.h"

ABYGameState::ABYGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABYGameState::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->OnWorldBeginPlay.AddUObject(this, &ABYGameState::OnAllActorsBeginPlayCompleted);
}
void ABYGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABYGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameState == EBYGameState::Ingame)
	{
		EnemySpawnElapsedTime += DeltaTime;
		if (EnemySpawnElapsedTime >= EnemySpawnTime)
		{
			EnemySpawnElapsedTime -= EnemySpawnTime;
			SpawnEnemyInFanShape();
		}
	}
}

void ABYGameState::OnAllActorsBeginPlayCompleted()
{
	SetGameState(EBYGameState::Menu);
}

void ABYGameState::SetGameState(EBYGameState InGameState)
{
	GameState = InGameState;

	switch (InGameState)
	{
	case EBYGameState::Menu:
		{
			if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
			{
				AM->DespawnPlayerPawn();
			}
		}
		break;
	case EBYGameState::Ingame:
		{
			if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
			{
				AM->SpawnPlayerPawn();
			}

			if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
			{
				SM->PlayBGM(EBYBGMType::Ingame, 2.f);
			}

			SetGameLevelSetting(1);
		}
		break;
	case EBYGameState::Result:
		{
			EndGame();
		}
		break;
	}

	if (UBYWidgetManager* WM = GetWorld()->GetSubsystem<UBYWidgetManager>())
	{
		WM->SetWidgetType(InGameState);
	}
}

void ABYGameState::SpawnEnemyInFanShape()
{
	UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>();
	if (!AM)
		return;

	ABYPlayerPawn* PlayerPawn = AM->GetPlayerPawn();
	if (!PlayerPawn)
		return;

	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	PlayerLocation.Z = EnemyPosition_Z;

	// 부채꼴 계산
	FVector ForwardDirection = FVector(1.f, 0.f, 0.f);

	for (int32 i = 0; i < EnemySpawnCount; i++)
	{
		float RandomAngle = FMath::RandRange(EnemySpawnAngle_Min, EnemySpawnAngle_Max);

		// 전방 방향을 Z축으로 랜덤 회전
		FVector SpawnDirection = ForwardDirection.RotateAngleAxis(RandomAngle, FVector::UpVector);

		// 플레이어의 위치 + (회전된 방향 * 거리) = 최종 스폰 위치
		float SpawnDistance = FMath::RandRange(EnemySpawnDistance_Min, EnemySpawnDistance_Max);
		FVector SpawnLocation = PlayerLocation + (SpawnDirection * SpawnDistance);

		int32 EnemyType = FMath::RandRange((int32)EBYActorType::Enemy1, (int32)EBYActorType::Enemy5);

		if (ABYEnemyActor* SpawnedEnemy = AM->GetSpawnedActor<ABYEnemyActor>((EBYActorType)EnemyType))
		{
			SpawnedEnemy->SetActorLocation(SpawnLocation);

			// 적이 플레이어를 바라보게 회전
			FRotator LookAtRotation = (-SpawnDirection).Rotation();
			LookAtRotation.Pitch = 0.f;
			LookAtRotation.Roll = 0.f;
			SpawnedEnemy->SetActorRotation(LookAtRotation);

			float EnemySpeed = FMath::RandRange(EnemySpeedMin, EnemySpeedMax);
			SpawnedEnemy->SetEnemy(PlayerPawn, CurrentGameLevel, EnemyHP, EnemySpeed);
		}
	}
}

void ABYGameState::EndGame()
{
	if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
	{
		AM->ReturnToPoolAll();
	}

	if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
	{
		SM->PlaySound2D(EBYSFXType::GameOver_BGM);
		SM->PlaySound2D(EBYSFXType::GameOver_Voice);

		SM->StopBGM();
	}
}

void ABYGameState::OnEnemyDie(int32 InEnemyLevel)
{
	int CurrentLevel = CurrentGameLevel;
	if (CurrentLevel == 0 || CurrentLevel != InEnemyLevel || NextLevelKillCount == 0)
		return;

	CurrentKillCount += 1;

	if (CurrentKillCount >= NextLevelKillCount)
	{
		SetGameLevelSetting(CurrentGameLevel + 1);
	}
}

void ABYGameState::SetGameLevelSetting(int32 InLevel)
{
	const UBYGameLevelSettings* GL = GetDefault<UBYGameLevelSettings>();

	if (!GL || !GL->GameLevelSettingsMap.Contains(InLevel))
		return;

	FBYGameLevelData Settings = GL->GameLevelSettingsMap[InLevel];

	CurrentGameLevel		= Settings.Level;
	NextLevelKillCount		= Settings.NextLevelKillCount; 

	BulletCount				= Settings.BulletCount;
	BulletSpeed				= Settings.BulletSpeed;
	BulletSpreadAngle		= Settings.BulletSpreadAngle;
	FireAttackTime			= Settings.FireAttackTime;
	FireDamage				= Settings.FireDamage;

	EnemySpawnCount			= Settings.EnemySpawnCount;
	EnemySpawnTime			= Settings.EnemySpawnTime;
	EnemyHP					= Settings.EnemyHP;
	EnemyDamage				= Settings.EnemyDamage;
	EnemySpawnDistance_Min  = Settings.EnemySpawnDistance_Min;
	EnemySpawnDistance_Max	= Settings.EnemySpawnDistance_Max;
	EnemySpawnAngle_Min		= Settings.EnemySpawnAngle_Min;
	EnemySpawnAngle_Max		= Settings.EnemySpawnAngle_Max;
	EnemySpeedMin			= Settings.EnemySpeedMin;
	EnemySpeedMax			= Settings.EnemySpeedMax;

	CurrentKillCount		= 0;

	if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
	{
		if (ABYPlayerPawn* PlayerPawn = AM->GetPlayerPawn())
		{
			PlayerPawn->SetPlayerLevel(CurrentGameLevel, BulletCount, BulletSpeed, BulletSpreadAngle, FireAttackTime, FireDamage);
		}
	}
}