// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NovaGameplayAbility.h"
#include "Ability/Task/NovaAbilityTask_MontageAndEvent.h"
#include "AbilitySystemComponent.h"

#include "Character/CharacterBase.h"

#include "NovaLogChannels.h"

UNovaGameplayAbility::UNovaGameplayAbility()
	:PlaySectionName(NAME_None)
{
}

void UNovaGameplayAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UNovaGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo) || !AbilityMontage)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	UNovaAbilityTask_MontageAndEvent* PlayMontageAndWaitForEvent = 	UNovaAbilityTask_MontageAndEvent::PlayMontageAndWaitForEvent(
			this,
			NAME_None,
			AbilityMontage,
			FGameplayTagContainer(),
			1.f,
			PlaySectionName);

	if (PlayMontageAndWaitForEvent)
	{
		PlayMontageAndWaitForEvent->OnCancelled.AddDynamic(this, &UNovaGameplayAbility::OnAbilityCancelled);
		PlayMontageAndWaitForEvent->OnCompleted.AddDynamic(this, &UNovaGameplayAbility::OnMontageCompleted);
		PlayMontageAndWaitForEvent->EventReceived.AddDynamic(this, &UNovaGameplayAbility::EventReceived);

		PlayMontageAndWaitForEvent->ReadyForActivation();
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	InitAbility();
}

ACharacterBase* UNovaGameplayAbility::GetCharacterBaseFromActorInfo()
{
	return CurrentActorInfo ? Cast< ACharacterBase>(CurrentActorInfo->AvatarActor.Get()) : nullptr;
}

void UNovaGameplayAbility::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	OnAbilityEvent(EventTag, EventData);
	OnAbilityEventBP(EventTag, EventData);
}

void UNovaGameplayAbility::InitAbility()
{
}

void UNovaGameplayAbility::OnAbilityEvent(FGameplayTag EventTag, FGameplayEventData EventData)
{
}

void UNovaGameplayAbility::OnEndAbility()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UNovaGameplayAbility::OnMontageEnded(UAnimMontage* PlayMotnage, bool bInterrupted)
{
	OnEndAbility();
}

void UNovaGameplayAbility::OnMontageCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	OnEndAbility();
}

void UNovaGameplayAbility::OnAbilityCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	OnEndAbility();
}
