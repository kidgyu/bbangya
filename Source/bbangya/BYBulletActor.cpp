// BYBulletActor.cpp

#include "BYBulletActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BYActorManager.h" // Ç® ¹Ý³³
#include "BYEnemyActor.h"
#include "BYEffectActor.h"
#include "BYTypes.h"

ABYBulletActor::ABYBulletActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(15.f);
	CollisionComp->SetGenerateOverlapEvents(true);
	CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = CollisionComp;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABYBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckHit(DeltaTime))
		return;
	
	if (GetActorLocation().SizeSquared() > MAX_DISTANCE)
	{
		UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>();
		if (AM)
		{
			AM->ReturnToPool(EBYActorType::Bullet, this);
		}
	}
}

void ABYBulletActor::LaunchBullet(const FVector PlayerPos, const FVector& Position, const FVector& Direction, const FRotator& Rotation, float InDamage, float InSpeed)
{
	PlayerPosition = PlayerPos;
	SetActorLocation(Position);
	SetActorRotation(Rotation);
	MoveDirection = Direction;
	Damage = InDamage;
	MoveSpeed = InSpeed;
}

bool ABYBulletActor::CheckHit(float DeltaTime)
{
	FHitResult HitResult;
	AddActorWorldOffset(MoveDirection * MoveSpeed * DeltaTime, true, &HitResult);

	if (HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor != this)
		{
			if (ABYActor* BYActor = Cast<ABYActor>(HitActor))
			{
				if (BYActor->IsEnemyActor())
				{
					if (ABYEnemyActor* Enemy = Cast<ABYEnemyActor>(BYActor))
					{
						Enemy->OnDamage(Damage);

						if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
						{							
							AM->ReturnToPool(EBYActorType::Bullet, this);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}