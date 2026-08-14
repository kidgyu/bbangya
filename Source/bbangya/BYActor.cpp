// Fill out your copyright notice in the Description page of Project Settings.


#include "BYActor.h"
#include "BYTypes.h"

// Sets default values
ABYActor::ABYActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABYActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABYActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABYActor::SetActorType(EBYActorType InType)
{
	ActorType = InType;
}

bool ABYActor::IsEnemyActor()
{
	return ActorType == EBYActorType::Enemy1
		|| ActorType == EBYActorType::Enemy2
		|| ActorType == EBYActorType::Enemy3
		|| ActorType == EBYActorType::Enemy4
		|| ActorType == EBYActorType::Enemy5;
}