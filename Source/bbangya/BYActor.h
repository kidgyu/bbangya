// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BYActor.generated.h"

enum class EBYActorType : uint8;

UCLASS()
class BBANGYA_API ABYActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABYActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetActorType(EBYActorType InType);
	EBYActorType GetActorType() { return ActorType; }
	bool IsEnemyActor();

protected:
	EBYActorType ActorType;
	float MoveSpeed = 0.f;
};
