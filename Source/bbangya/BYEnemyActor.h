// BYEnemyActor.h

#pragma once

#include "CoreMinimal.h"
#include "BYActor.h"
#include "BYEnemyActor.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class ABYPlayerPawn;

UCLASS()
class BBANGYA_API ABYEnemyActor : public ABYActor
{
	GENERATED_BODY()
	
public:	
	ABYEnemyActor();
	virtual void Tick(float DeltaTime) override;
	void SetEnemy(ABYPlayerPawn* Player, int32 InLevel, float InHP, float InMoveSpeed);
	void OnDamage(float DamageAmount);

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void OnPlayDieAnimation(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void OnCompleteDieAnimation();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 EnemyLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsEnemyDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float EnemyHP = 0.f;



private:
	FVector EnemyMoveForward;
	TWeakObjectPtr<ABYPlayerPawn> TargetPlayer;
};
