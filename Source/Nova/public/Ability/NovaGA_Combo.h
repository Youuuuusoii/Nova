// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ability/NovaGameplayAbility.h"
#include "NovaGA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UNovaGA_Combo : public UNovaGameplayAbility
{
	GENERATED_BODY()

public:
	UNovaGA_Combo();

protected:
	int32	SectionID;
	bool	bInputEvent;

	TObjectPtr<class ACharacterBase>	ActorInfoCharacter;
	TObjectPtr<class UCharacterAnimInstance>		CharacterAnim;
	
protected:
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void OnAbilityEvent(FGameplayTag EventTag, FGameplayEventData EventData) override;
	virtual void OnEndAbility() override;
	virtual void InitAbility() override;
};
