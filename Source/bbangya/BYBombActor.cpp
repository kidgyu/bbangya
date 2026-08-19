// BYBombActor.cpp

#include "BYBombActor.h"
#include "Components/StaticMeshComponent.h"
#include "BYEnemyActor.h"
#include "BYActorManager.h"
#include "BYEffectActor.h"
#include "BYSoundManager.h"
#include "Engine/OverlapResult.h"
#include "BYTypes.h"

ABYBombActor::ABYBombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);
}

void ABYBombActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABYBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsExploded)
		return;

	CurrentVelocity.Z -= DropSpeed * DeltaTime;
	AddActorWorldOffset(CurrentVelocity * DeltaTime, true);

	if (GetActorLocation().Z <= 10.f)
	{
		Explode();
	}
}

void ABYBombActor::LaunchBomb(const FVector& StartLocation, const FVector& ThrowDirection)
{
	SetActorLocation(StartLocation);

	bIsExploded = false;
	CurrentVelocity = (ThrowDirection * MoveSpeed) + FVector(0.f, 0.f, UpSpeed);
}

void ABYBombActor::Explode()
{
	bIsExploded = true;
	FVector ExplodeLocation = GetActorLocation();

	FCollisionShape Sphere = FCollisionShape::MakeSphere(ExplosionRadius);
	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		ExplodeLocation,
		FQuat::Identity,
		ECC_Pawn,
		Sphere,
		QueryParams
	);

	if (bHit)
	{
		for (FOverlapResult& Result : OverlapResults)
		{
			if (ABYEnemyActor* Enemy = Cast<ABYEnemyActor>(Result.GetActor()))
			{
				Enemy->OnDamage(9999.f);
			}
		}

		if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
		{
			if (ABYEffectActor* EA = AM->GetSpawnedActor<ABYEffectActor>(EBYActorType::Effect_Explosion))
			{
				EA->PlayEffect(GetActorLocation());
			}

			AM->ReturnToPool(GetActorType(), this);
		}

		if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
		{
			SM->PlaySound2D(EBYSFXType::Explode);
		}
	}

	
}