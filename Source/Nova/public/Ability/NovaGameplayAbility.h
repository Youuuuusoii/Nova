// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "NovaGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UNovaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UNovaGameplayAbility();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nova|Animation")
	UAnimMontage* AbilityMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nova|Animation")
	FName PlaySectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nova|Tag")
	FGameplayTag	AbilitytTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nova|Tag")
	FGameplayTag	CooldownTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nova|GameplayEffect")
	TMap<FGameplayTag, TSubclassOf <UGameplayEffect>> EffectContainerMap;	

public:
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	class ACharacterBase* GetCharacterBaseFromActorInfo();

	UFUNCTION(BlueprintCallable)
	void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION(BlueprintImplementableEvent, Category = "Nova|Ability")
	void OnAbilityEventBP(FGameplayTag EventTag, FGameplayEventData EventData);

protected:
	virtual void InitAbility();
	virtual void OnAbilityEvent(FGameplayTag EventTag, FGameplayEventData EventData);
	virtual void OnEndAbility();

	UFUNCTION(BlueprintCallable)
	virtual void OnMontageEnded(UAnimMontage* PlayMotnage, bool bInterrupted);

	UFUNCTION()
	void OnMontageCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnAbilityCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnAbilityInterrupted(FGameplayTag EventTag, FGameplayEventData EventData);
};
