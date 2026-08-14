// BYPlayerPawn.cpp

#include "BYPlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "NiagaraComponent.h"
#include "BYGameState.h"
#include "BYActorManager.h"
#include "BYSoundManager.h"
#include "BYBulletActor.h"
#include "BYTypes.h"

ABYPlayerPawn::ABYPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RootComp);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComp);
	SpringArm->TargetArmLength = 200.f;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(SkeletalMesh, FName("WeaponSocket_R"));

	NS_Burst = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSSmoke"));
	NS_Burst->SetupAttachment(Weapon);
	FName ParameterName = TEXT("User.Scale");
	NS_Burst->SetFloatParameter(ParameterName, 0.3f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SingleMontageObj(TEXT("/Game/Animation/AM_Pistol_Shoot.AM_Pistol_Shoot"));
	if (SingleMontageObj.Succeeded())
	{
		SingleShotMontage = SingleMontageObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BurstMontageObj(TEXT("/Game/Animation/AM_Pistol_Shoot_Burst.AM_Pistol_Shoot_Burst"));
	if (BurstMontageObj.Succeeded())
	{
		BurstShotMontage = BurstMontageObj.Object;
	}
}

void ABYPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GameState = GetWorld()->GetGameState<ABYGameState>();
	IsPlayerDie = false;
}

void ABYPlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GameState = nullptr;

	Super::EndPlay(EndPlayReason);
}

void ABYPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameState)
	{
		if (GameState->GetCurrentGameState() != EBYGameState::Ingame)
		{
			return;
		}
	}

	ElapsedTime += DeltaTime;
	if (ElapsedTime >= CurrentFireTime)
	{
		ElapsedTime -= CurrentFireTime;
		FireBullet();
	}
}

void ABYPlayerPawn::SetPlayerLevel(int32 InGameLevel, int32 InBulletCount, float InBulletSpeed, float InBulletSpreadAngle, float InFireAttackTime, float InFireDamage)
{
	GameLevel			= InGameLevel;
	NumberOfShots		= InBulletCount;
	BulletSpeed			= InBulletSpeed;
	BulletSpreadAngle	= InBulletSpreadAngle;
	CurrentFireTime		= InFireAttackTime;
	Damage				= InFireDamage;

	if (GameLevel >= BurstLevel)
	{
		NS_Burst->Activate(true);

		int LevelGap = GameLevel - BurstLevel;
		FName ParameterName = TEXT("User.Scale");
		if (LevelGap == 0)		
			NS_Burst->SetFloatParameter(ParameterName, 0.2f);
		else if (LevelGap == 1) 
			NS_Burst->SetFloatParameter(ParameterName, 0.4f);
		else if (LevelGap == 2)
			NS_Burst->SetFloatParameter(ParameterName, 0.6f);
		else if (LevelGap >= 3)
			NS_Burst->SetFloatParameter(ParameterName, 0.8f);
	}
	else
	{
		NS_Burst->Deactivate();
	}
}

void ABYPlayerPawn::FireBullet()
{
	UAnimInstance* AnimIntance = SkeletalMesh->GetAnimInstance();
	if (AnimIntance)
	{
		if (CurrentFireTime >= FireBurstTime) // 임의 지정 테스트
		{
			OnPlayShootAnimation(false);
			/*if (SingleShotMontage)
			{
				AnimIntance->Montage_Stop(0.f, SingleShotMontage);
				AnimIntance->Montage_Play(SingleShotMontage);
			}*/
		}
		else
		{
			OnPlayShootAnimation(true);
			/*if (BurstShotMontage)
			{
				AnimIntance->Montage_Stop(0.f, BurstShotMontage);
				AnimIntance->Montage_Play(BurstShotMontage, 1.f, EMontagePlayReturnType::MontageLength, 0.f, true);
			}*/
		}
	}

	if (!Weapon)
		return;

	UBYActorManager* AM = GetWorld()->GetSubsystem<UBYActorManager>();
	if (!AM)
		return;
	
	FVector FireDirection = GetActorForwardVector();
	FVector FirePosition = Weapon->GetComponentLocation() + (FireDirection * 4.f);
	FRotator FireRotation = GetActorRotation();
	
	if (NumberOfShots <= 1)
	{
		ABYBulletActor* Bullet = AM->GetSpawnedActor<ABYBulletActor>(EBYActorType::Bullet);
		if (Bullet)
		{
			Bullet->LaunchBullet(GetActorLocation(), FirePosition, FireDirection, FireRotation, Damage, BulletSpeed);
		}
	}
	else
	{
		float TotalSpreadWidth = (NumberOfShots - 1) * BulletSpreadAngle;
		float StartAngle = -TotalSpreadWidth / 2.f;

		for (int32 i = 0; i < NumberOfShots; i++)
		{
			float CurrentAngle = StartAngle + (i * BulletSpreadAngle);
			FVector ShotDirection = FireDirection.RotateAngleAxis(CurrentAngle, FVector::UpVector);
			FRotator ShotRotation = ShotDirection.Rotation();

			ABYBulletActor* Bullet = AM->GetSpawnedActor<ABYBulletActor>(EBYActorType::Bullet);
			if (Bullet)
			{
				Bullet->LaunchBullet(GetActorLocation(), FirePosition, ShotDirection, ShotRotation, Damage, BulletSpeed);
			}
		}
	}

	if (UBYSoundManager* SM = GetWorld()->GetSubsystem<UBYSoundManager>())
	{
		SM->PlaySound2D(EBYSFXType::Shot);
	}
}

void ABYPlayerPawn::OnDamage(float DamageAmount)
{
	if (!GameState || GameState->GetCurrentGameState() != EBYGameState::Ingame)
		return;

	PlayerHP = FMath::Max(PlayerHP - DamageAmount, 0.f);
	if (FMath::IsNearlyZero(PlayerHP))
	{
		GameState->SetGameState(EBYGameState::Result);
		IsPlayerDie = true;

		int32 RandIndex = FMath::RandRange(0, 3);
		OnPlayDieAnimation(RandIndex);
	}
}