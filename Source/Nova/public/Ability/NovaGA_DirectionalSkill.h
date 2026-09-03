// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/NovaGameplayAbility.h"
#include "NovaGA_DirectionalSkill.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UNovaGA_DirectionalSkill : public UNovaGameplayAbility
{
	GENERATED_BODY()

public:
	UNovaGA_DirectionalSkill();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(BlueprintReadOnly)
	FVector Direction;

protected:
	void CalculationActorDirection();
};
