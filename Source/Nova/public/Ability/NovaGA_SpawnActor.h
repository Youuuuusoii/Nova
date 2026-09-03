// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/NovaGameplayAbility.h"
#include "NovaGA_SpawnActor.generated.h"

/**
 * 
 */

//헤더로 변경 예정
USTRUCT(BlueprintType)
struct FSpawnTransform
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector	SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector	SpawnDistance;
};
class ANovaAbilityActor;
UCLASS()
class NOVA_API UNovaGA_SpawnActor : public UNovaGameplayAbility
{
	GENERATED_BODY()

public:
	UNovaGA_SpawnActor();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Nova|AbilityActor")
	TSubclassOf<ANovaAbilityActor>	AbilitySpawnActorClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Nova|AbilityActor")
	FSpawnTransform	ActorSpawnTransform;

protected:
	virtual void OnAbilityEvent(FGameplayTag EventTag, FGameplayEventData EventData) override;

private:
	void SpawnActor();
};
