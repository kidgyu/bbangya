// BYBombActor.h

#pragma once

#include "CoreMinimal.h"
#include "BYActor.h"
#include "BYBombActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class BBANGYA_API ABYBombActor : public ABYActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABYBombActor();
	void LaunchBomb(const FVector& StartLocation, const FVector& ThrowDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Explode();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UStaticMeshComponent> MeshComp;

private:
	bool bIsExploded = false;
	float ExplosionRadius = 300.f;
	float MoveSpeed = 1000.f;
	float UpSpeed = 800.f;
	float DropSpeed = 3000.f;
	FVector CurrentVelocity;
};
