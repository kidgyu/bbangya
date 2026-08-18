// Fill out your copyright notice in the Description page of Project Settings.


#include "BYActorManager.h"
#include "BYPlayerPawn.h"
#include "BYTypes.h"
#include "BYActor.h"
#include "BYGameData.h"
#include "BYEnemyActor.h"

void UBYActorManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PlayerPawnClass = TSoftClassPtr<ABYPlayerPawn>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYPlayerPawn.BP_BYPlayerPawn_C")));
}

void UBYActorManager::Deinitialize()
{
	if (IsValid(PlayerPawn))
	{
		PlayerPawn->Destroy();
	}
	PlayerPawn = nullptr;

	Super::Deinitialize();
}

void UBYActorManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	PreLoadActorPool();
}

void UBYActorManager::SpawnPlayerPawn()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
		return;

	TSubclassOf<ABYPlayerPawn> PawnClassToSpawn = PlayerPawnClass.LoadSynchronous();
	if (!IsValid(PawnClassToSpawn))
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector SpawnLocation = FVector(0.f, 0.f, 1.f);
	FRotator SpawnRotaion = FRotator::ZeroRotator;

	if (IsValid(PlayerPawn))
	{
		PlayerPawn->SetActorHiddenInGame(false);
		PlayerPawn->SetActorLocation(SpawnLocation);
		PlayerPawn->SetActorRotation(SpawnRotaion);
	}
	else
	{
		PlayerPawn = World->SpawnActor<ABYPlayerPawn>(PawnClassToSpawn, SpawnLocation, SpawnRotaion, SpawnParams);
		if (!IsValid(PlayerPawn))
			return;

		APlayerController* PC = World->GetFirstPlayerController();
		if (!IsValid(PC))
			return;

		PC->Possess(PlayerPawn);
		PC->SetViewTarget(PlayerPawn);
	}

	PlayerPawn->InitPlayer();
}

void UBYActorManager::DespawnPlayerPawn()
{
	if (IsValid(PlayerPawn))
	{
		PlayerPawn->SetActorHiddenInGame(true);
	}
}

ABYActor* UBYActorManager::GetSpawnedActor(EBYActorType ActorType)
{
	FBYActorPool& Pool = ActorPoolMap.FindOrAdd(ActorType);

	if (Pool.InactiveActors.Num() == 0)
	{
		PrepopulatePool(ActorType);
	}

	ABYActor* PoolActor = Pool.InactiveActors.Pop();
	SetActiveActor(PoolActor, true);
	Pool.ActiveActors.Add(PoolActor);

	return PoolActor;
}

void UBYActorManager::ReturnToPool(EBYActorType ActorType, ABYActor* Actor)
{
	FBYActorPool& Pool = ActorPoolMap.FindOrAdd(ActorType);
	if (Pool.ActiveActors.Contains(Actor))
	{
		Pool.ActiveActors.Remove(Actor);
	}
	Pool.InactiveActors.Add(Actor);
	SetActiveActor(Actor, false);
	Actor->SetActorLocation(FVector(0.f, 0.f, -99999.f));
}

void UBYActorManager::ReturnToPoolAll()
{
	for (auto& Pair : ActorPoolMap)
	{
		for (auto& Actor : Pair.Value.ActiveActors)
		{
			if (IsValid(Actor))
			{
				Pair.Value.InactiveActors.Add(Actor);
				SetActiveActor(Actor, false);
			}
		}
	}
}

void UBYActorManager::PrepopulatePool(EBYActorType ActorType, int32 Size)
{
	FBYActorPool& Pool = ActorPoolMap.FindOrAdd(ActorType);
	
	const UBYGameData* GameData = GetDefault<UBYGameData>();
	if (!IsValid(GameData) || !GameData->ActorClassMap.Contains(ActorType))
		return;

	TSubclassOf<ABYActor> ActorClass = GameData->ActorClassMap[ActorType].LoadSynchronous();

	if (!ActorClass)
		return;

	for (int32 i = 0; i < Size; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 풀용 대기 액터이므로 생성 시 충돌 조건 무시.
		ABYActor* NewActor = GetWorld()->SpawnActor<ABYActor>(ActorClass, FVector(0.f, 0.f, -99999.f), FRotator::ZeroRotator, SpawnParams);

		if (IsValid(NewActor))
		{
			SetActiveActor(NewActor, false);
			NewActor->SetActorType(ActorType);

			Pool.InactiveActors.Add(NewActor);
		}
	}
}

void UBYActorManager::PreLoadActorPool()
{
	for (int32 i = 0; i < (int32)EBYActorType::MAX; i++)
	{
		EBYActorType Type = (EBYActorType)i;

		PrepopulatePool(Type, 200);
	}
}

void UBYActorManager::SetActiveActor(ABYActor* InActor, bool InActive)
{
	InActor->SetActorHiddenInGame(!InActive); // 렌더링
	InActor->SetActorTickEnabled(InActive); // 업데이트
	InActor->SetActorEnableCollision(InActive); // 충돌
}

void UBYActorManager::SetPlayerRotationAngle(float InMin, float InMax)
{
	PlayerRotationAngleMin = InMin;
	PlayerRotationAngleMax = InMax;
}