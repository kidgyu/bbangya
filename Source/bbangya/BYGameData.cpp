// BYGameData.cpp

#include "BYGameData.h"
#include "BYActor.h"

UBYGameData::UBYGameData()
{
	CategoryName = TEXT("Game");
	SectionName = TEXT("By Game Data");

	ActorClassMap.Add(EBYActorType::Enemy1, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEnemy1_A.BP_BYEnemy1_A_C"))));
	ActorClassMap.Add(EBYActorType::Enemy2, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEnemy2_A.BP_BYEnemy2_A_C"))));
	ActorClassMap.Add(EBYActorType::Enemy3, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEnemy3_A.BP_BYEnemy3_A_C"))));
	ActorClassMap.Add(EBYActorType::Enemy4, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEnemy4_A.BP_BYEnemy4_A_C"))));
	ActorClassMap.Add(EBYActorType::Enemy5, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEnemy5_A.BP_BYEnemy5_A_C"))));

	ActorClassMap.Add(EBYActorType::Bomb, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYBombActor.BP_BYBombActor_C"))));
	ActorClassMap.Add(EBYActorType::Bullet, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYBulletActor.BP_BYBulletActor_C"))));

	ActorClassMap.Add(EBYActorType::Effect_Hit, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEffectHitActor.BP_BYEffectHitActor_C"))));
	ActorClassMap.Add(EBYActorType::Effect_Die, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEffectDieActor.BP_BYEffectDieActor_C"))));
	ActorClassMap.Add(EBYActorType::Effect_Explosion, TSoftClassPtr<ABYActor>(FSoftObjectPath(TEXT("/Game/Actor/BP_BYEffectExplosionActor.BP_BYEffectExplosionActor_C"))));
	
}