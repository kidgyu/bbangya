// BYEnemyActor.cpp

#include "BYEnemyActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BYGameState.h"
#include "BYActorManager.h"
#include "BYSoundManager.h"
#include "BYPlayerPawn.h"
#include "BYEffectActor.h"
#include "BYTypes.h"

ABYEnemyActor::ABYEnemyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
}

void ABYEnemyActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABYEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsEnemyDie)
		return;

	if (TargetPlayer.IsValid())
	{
		FVector CurrentLocation = GetActorLocation();
		FVector PlayerLocation = TargetPlayer->GetActorLocation();
		PlayerLocation.Z = CurrentLocation.Z;
		FVector Direction = PlayerLocation - CurrentLocation;
		float Distance = Direction.Size();
		Direction.Normalize();
		
		float CollisionRange = TargetPlayer->GetDamageRange();
		if (Distance <= CollisionRange)
		{
			TargetPlayer->OnDamage(AttackDamage);
			UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>();
			if (AM)
			{
				if (ABYEffectActor* EffectActor = AM->GetSpawnedActor<ABYEffectActor>(EBYActorType::Effect_Die))
				{
					EffectActor->PlayEffect(GetActorLocation());
				}

				if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
				{
					SM->PlaySound2D(EBYSFXType::PlayerHurt);
				}

				AM->ReturnToPool(GetActorType(), this);
			}

			return;
		}

		FVector AvoidanceVector = FVector::Zero();
		// 스피어 트레이스를 발사해 전방 감지
		float AvoidanceCheckDistance = 50.f;
		FVector CheckCenter = CurrentLocation + Direction * AvoidanceCheckDistance;
		float AvoidanceCheckRadius = CapsuleComp->GetScaledCapsuleRadius() * 1.5f; // 내 캡슐보다 조금 더 넓은 반경

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this); // 자기 자신 제외

		//감지할 오브젝트 타입들
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		// 겹쳐진 액터들을 담을 배열
		TArray<AActor*> OverlappedActors;

		bool bHasNeighbor = UKismetSystemLibrary::SphereOverlapActors(
			GetWorld(),
			CheckCenter,					//  // 내 살짝 앞이 중심점
			AvoidanceCheckRadius,			// 감지 반경
			ObjectTypes,					// Pawn 채널만
			ABYEnemyActor::StaticClass(),	// 검색할 특정 클래스
			ActorsToIgnore,					// 나 자신 제외
			OverlappedActors				// 결과
		);

		if (bHasNeighbor && OverlappedActors.Num() > 0)
		{
			AActor* OtherEnemy = OverlappedActors[0]; // 가장 가까이 겹친 적을 타겟으로
			if (IsValid(OtherEnemy))
			{
				FVector RightVector = FVector::CrossProduct(Direction, FVector::UpVector);

				// 상대 액터가 나의 좌/우 어디에 있는지 체크
				FVector DirToHitActor = (OtherEnemy->GetActorLocation() - CurrentLocation).GetSafeNormal();
				float DotProduct = FVector::DotProduct(DirToHitActor, RightVector);

				// 오른쪽에 있으면 왼쪽, 왼쪽에 있으면 오른쪽으로 회피
				AvoidanceVector = -RightVector * FMath::Sign(DotProduct) * 4.f; // 마지막 : 회피 강도
			}
		}

		FVector FinalDirection = Direction + AvoidanceVector;
		FinalDirection.Normalize();

		AddActorWorldOffset(FinalDirection * MoveSpeed * DeltaTime, true);

		FRotator TargetRotation = Direction.Rotation();
		TargetRotation.Pitch = 0.f;
		TargetRotation.Roll = 0.f;
		SetActorRotation(TargetRotation);
	}
}

void ABYEnemyActor::SetEnemy(ABYPlayerPawn* Player, int32 InLevel, float InHP, float InMoveSpeed)
{
	EnemyLevel	= InLevel;
	EnemyHP		= InHP;
	MoveSpeed	= InMoveSpeed;

	TargetPlayer = Player;
	IsEnemyDie = false;

	SkeletalMesh->InitializeAnimScriptInstance(true);
}

void ABYEnemyActor::OnDamage(float DamageAmount)
{
	EnemyHP -= DamageAmount;
	if (EnemyHP <= 0.f)
	{
		if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
		{
			if (ABYEffectActor* EffectActor = AM->GetSpawnedActor<ABYEffectActor>(EBYActorType::Effect_Die))
			{
				EffectActor->PlayEffect(GetActorLocation());
			}

			if (ABYEffectActor* EffectActor = AM->GetSpawnedActor<ABYEffectActor>(EBYActorType::Effect_Hit))
			{
				FVector HitPos = GetActorLocation();
				FVector DirToPlayer = FVector::ZeroVector;
				if (TargetPlayer.IsValid())
				{
					DirToPlayer = TargetPlayer->GetActorLocation() - HitPos;
					DirToPlayer.Z = 0.f;
				}				

				EffectActor->PlayEffect(HitPos + (DirToPlayer.GetSafeNormal() * 50.f));
			}
		}

		if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
		{
			SM->PlaySound2D(EBYSFXType::Die);
		}

		if (ABYGameState* GS = GetWorld()->GetGameState<ABYGameState>())
		{
			GS->OnEnemyDie(EnemyLevel);
		}

		int32 RandIndex = FMath::RandRange(0, 3);
		OnPlayDieAnimation(RandIndex);

		SetActorEnableCollision(false); // 충돌
		IsEnemyDie = true;
	}
}

void ABYEnemyActor::OnCompleteDieAnimation()
{
	if (UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>())
	{
		AM->ReturnToPool(ActorType, this);
	}
}