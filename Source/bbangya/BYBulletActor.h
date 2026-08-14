// BYBulletActor.h

#pragma once

#include "CoreMinimal.h"
#include "BYActor.h"
#include "BYBulletActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class BBANGYA_API ABYBulletActor : public ABYActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABYBulletActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchBullet(const FVector PlayerPos, const FVector& Position, const FVector& Direction, const FRotator& Rotation, float InDamage, float InSpeed);

private:
	bool CheckHit(float DeltaTime);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BulletMesh;

protected:
	FVector PlayerPosition;
	FVector MoveDirection;
	float Damage = 1.f;
	
	const float MAX_DISTANCE = 1000000.f;
};
