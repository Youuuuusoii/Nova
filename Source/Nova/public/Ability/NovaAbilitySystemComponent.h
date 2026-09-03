// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NovaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UNovaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UNovaAbilitySystemComponent();

protected:
	TArray<FGameplayAbilitySpecHandle>	InputTriggeredSpecHandles;
	TArray<FGameplayAbilitySpecHandle>	InputCompletedSpecHandles;

private:
	bool bASCInitialize;

public:
	bool bIsASCInitialize() const {	return bASCInitialize;	}
	void ASCInitializeCompleted() { bASCInitialize = true; }

	void AbilityInputTriggered(const FGameplayTag& InputTag);
	void AbilityInputCompleted(const FGameplayTag& InputTag);
	void ProcessAbilityInput(float DeltaTime, bool bGamePaused = false);
	bool TryActivateAbilityByTag(const FGameplayTag& AbilityTag);	
};
