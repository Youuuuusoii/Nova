// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NovaAbilityActor.generated.h"

struct FGameplayEffectSpecHandle;

UCLASS()
class NOVA_API ANovaAbilityActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ANovaAbilityActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent>	MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	LifeTime;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void ActivateAbilityActor(AActor* AbilityActorInstigator, FGameplayEffectSpecHandle DamangeSpec);
};
