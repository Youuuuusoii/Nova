// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NovaAbilitySystemComponent.h"

UNovaAbilitySystemComponent::UNovaAbilitySystemComponent()
	: bASCInitialize(false)
{
}

void UNovaAbilitySystemComponent::AbilityInputTriggered(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				InputTriggeredSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UNovaAbilitySystemComponent::AbilityInputCompleted(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				InputCompletedSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UNovaAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	static TArray<FGameplayAbilitySpecHandle> AbilityToActivateSpecHandle;
	AbilityToActivateSpecHandle.Reset();

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : InputTriggeredSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilitySpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;

				if (AbilitySpec->IsActive())	//실행중이면
				{
					//입력 콜
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					//실행중이지 않은 것들만 실행시키기 위해서
					AbilityToActivateSpecHandle.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& ActivateAbilitySpecHandle : AbilityToActivateSpecHandle)
	{
		TryActivateAbility(ActivateAbilitySpecHandle);	//실행함수
	}

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : InputCompletedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilitySpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;

				if (AbilitySpec->IsActive())	//실행중이면
				{
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}

	InputTriggeredSpecHandles.Reset();
	InputCompletedSpecHandles.Reset();
}

bool UNovaAbilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag& AbilityTag)
{
	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(AbilityTag))
		{
			return TryActivateAbility(AbilitySpec.Handle);
		}
	}

	return false;
}
