// BYEffectActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BYActor.h"
#include "BYEffectActor.generated.h"

enum class EBYActorType : uint8;
class UNiagaraComponent;

UCLASS()
class BBANGYA_API ABYEffectActor : public ABYActor
{
	GENERATED_BODY()
	
public:	
	ABYEffectActor();

protected:
	virtual void BeginPlay() override;

public:	
	void PlayEffect(const FVector& InLocation);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effect")
	TObjectPtr<UNiagaraComponent> EffectComp;

	UFUNCTION()
	void OnEffectFinished(UNiagaraComponent* PSystem);
};
