// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/Actors/NovaAbilityActor.h"
#include "NovaAbilitySpawner.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EActorSpawnType : uint8
{
	Immediate,
	Delayed
};

class ANovaPooledActor;

UCLASS()
class NOVA_API ANovaAbilitySpawner : public ANovaAbilityActor
{
	GENERATED_BODY()

public:
	ANovaAbilitySpawner();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> SpawnInstigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ANovaPooledActor>	PooledActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	ActorCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FTransform> SpawnActorsTransform;

	UPROPERTY(EditDefaultsOnly, Category = "Nova|Spawn")
	EActorSpawnType	SpawnType = EActorSpawnType::Immediate;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SpawnMode == ENovaSpawnMode::Delayed", EditConditionHides), Category = "Nova|Spawn")
	float	SpawnInterval = 0.1f;

	TArray<TObjectPtr<ANovaPooledActor>>	PooledActors;
	FTimerHandle	TimerHandle;
	int32 CurrentSpawnIndex;

public:
	virtual void ActivateAbilityActor(AActor* AbilityActorInstigator, FGameplayEffectSpecHandle DamangeSpec) override;

protected:
	virtual void BeginPlay() override;

	void ImmediateSpawnActors();

	UFUNCTION()
	void ProcessNextSpawn();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PooledActorSetTransform();
};
