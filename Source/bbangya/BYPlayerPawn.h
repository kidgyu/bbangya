// BYPlayerPawn.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BYPlayerPawn.generated.h"

class ABYGameState;

UCLASS()
class BBANGYA_API ABYPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ABYPlayerPawn();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetPlayerLevel(int32 InGameLevel, int32 InBulletCount, float InBulletSpeed, float InBulletSpreadAngle, float InFireAttackTime, float InFireDamage);
	
private:
	void FireBullet();

public:
	UFUNCTION(BlueprintPure, Category = "Combat")
	float GetDamageRange() const { return DamageRange; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnDamage(float DamageAmount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void OnPlayIdleAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void OnPlayShootAnimation(bool bIsBurst);

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void OnPlayDieAnimation(int32 Index);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USceneComponent> RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UNiagaraComponent> NS_Burst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimMontage> SingleShotMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimMontage> BurstShotMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float PlayerHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BulletSpeed = 3500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 NumberOfShots = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BulletSpreadAngle = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float CurrentFireTime = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsPlayerDie = false;

	UPROPERTY()
	TObjectPtr<ABYGameState> GameState;

private:
	int32 GameLevel = 1;
	int32 BurstLevel = 4;
	float ElapsedTime = 0.f;
	const float FireBurstTime = 0.2f;
};
