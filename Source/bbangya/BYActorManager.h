// BYActorManager.h

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BYActorManager.generated.h"

class ABYPlayerPawn;
class ABYActor;

enum class EBYActorType : uint8;

USTRUCT(BlueprintType)
struct FBYActorPool
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<ABYActor>> ActiveActors;
	UPROPERTY()
	TArray<TObjectPtr<ABYActor>> InactiveActors;
};

UCLASS()
class BBANGYA_API UBYActorManager : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

public:
	void SpawnPlayerPawn();
	void DespawnPlayerPawn();

	ABYPlayerPawn* GetPlayerPawn() { return PlayerPawn; }
	void ReturnToPool(EBYActorType ActorType, ABYActor* Actor);
	void ReturnToPoolAll();
	void PrepopulatePool(EBYActorType ActorType, int32 Size = 20);

	void SetPlayerRotationAngle(float InMin, float InMax);
	float GetPlayerRotationAngleMin() { return PlayerRotationAngleMin - 10.f; }
	float GetPlayerRotationAngleMax() { return PlayerRotationAngleMax + 10.f; }
	FVector GetPlayerLocation();

	ABYActor* GetSpawnedActor(EBYActorType ActorType);

	template<typename T>
	T* GetSpawnedActor(EBYActorType ActorType)
	{
		return Cast<T>(GetSpawnedActor(ActorType));
	}

private:
	void PreLoadActorPool();
	void SetActiveActor(ABYActor* InActor, bool InActive);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Actor")
	TSoftClassPtr<ABYPlayerPawn> PlayerPawnClass; // 플레이어 폰 경로

	UPROPERTY(EditDefaultsOnly, Category = "Actor")
	TMap<EBYActorType, TSoftClassPtr<AActor>> ActorClassMap;
	
	UPROPERTY()
	TObjectPtr<ABYPlayerPawn> PlayerPawn;

	UPROPERTY()
	TMap<EBYActorType, FBYActorPool> ActorPoolMap;

private:
	float PlayerRotationAngleMin = 0.f;
	float PlayerRotationAngleMax = 0.f;
};
