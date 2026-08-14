// BYEffectActor.cpp

#include "BYEffectActor.h"
#include "NiagaraComponent.h"
#include "BYActorManager.h"

ABYEffectActor::ABYEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	EffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(RootComponent);

	EffectComp->bAutoActivate = false;
}

void ABYEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (EffectComp)
	{
		EffectComp->OnSystemFinished.AddDynamic(this, &ABYEffectActor::OnEffectFinished);
	}
}


void ABYEffectActor::PlayEffect(const FVector& InLocation)
{
	SetActorLocation(InLocation);
	
	if (EffectComp)
	{
		EffectComp->Activate(true);
	}
}

void ABYEffectActor::OnEffectFinished(UNiagaraComponent* PSystem)
{
	UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>();
	if (AM)
	{
		EffectComp->bAutoActivate = false;
		AM->ReturnToPool(GetActorType(), this);
	}
}