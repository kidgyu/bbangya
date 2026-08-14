// BYObstacleActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BYObstacleActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class BBANGYA_API ABYObstacleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABYObstacleActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UStaticMeshComponent> MeshComp;
};
