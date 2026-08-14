// BYObstacleActor.cpp

#include "BYObstacleActor.h"
#include "Components/StaticMeshComponent.h"

ABYObstacleActor::ABYObstacleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);
}

