#include "Ability/Task/NovaAbilityTask_MontageAndEvent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"

UNovaAbilityTask_MontageAndEvent::UNovaAbilityTask_MontageAndEvent()
{
	Rate = 1.f;
	bStopWhenAbilityEnds = true;
}

UNovaAbilityTask_MontageAndEvent* UNovaAbilityTask_MontageAndEvent::PlayMontageAndWaitForEvent(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay,
	FGameplayTagContainer EventTags, float Rate, FName StartSection,
	bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	// 태스크 생성 및 초기화
	UNovaAbilityTask_MontageAndEvent* MyObj = NewAbilityTask<UNovaAbilityTask_MontageAndEvent>(OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->EventTags = EventTags;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;

	return MyObj;
}

void UNovaAbilityTask_MontageAndEvent::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	bool bPlayedMontage = false;

	if (UAbilitySystemComponent* ASC = AbilitySystemComponent.Get())
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			// 게임플레이 이벤트 수신 바인딩
			EventHandle = ASC->AddGameplayEventTagContainerDelegate(EventTags, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UNovaAbilityTask_MontageAndEvent::OnGameplayEvent));

			// 몽타주 재생을 ASC에 위임하여 멀티플레이어 동기화 처리
			if (ASC->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection) > 0.f)
			{
				if (ShouldBroadcastAbilityTaskDelegates() == false)
				{
					return;
				}

				CancelledHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UNovaAbilityTask_MontageAndEvent::OnAbilityCancelled);

				// 몽타주 종료 델리게이트 바인딩
				FOnMontageEnded EndDelegate;
				EndDelegate = FOnMontageEnded::CreateUObject(this, &UNovaAbilityTask_MontageAndEvent::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(EndDelegate, MontageToPlay);
				AnimInstance->OnMontageBlendingOut.AddDynamic(this, &UNovaAbilityTask_MontageAndEvent::OnMontageBlendingOut);

				bPlayedMontage = true;
			}
		}
	}

	if (!bPlayedMontage)
	{
		// 재생 실패 시 취소
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void UNovaAbilityTask_MontageAndEvent::ExternalCancel()
{
	check(AbilitySystemComponent.IsValid());
	OnAbilityCancelled();
	Super::ExternalCancel();
}

void UNovaAbilityTask_MontageAndEvent::OnDestroy(bool AbilityEnded)
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}

	if (Ability)
	{
		Ability->OnGameplayAbilityCancelled.Clear();

		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->OnMontageBlendingOut.Clear();
		}
	}

	Super::OnDestroy(AbilityEnded);
}

void UNovaAbilityTask_MontageAndEvent::OnAbilityCancelled()
{
	if (StopPlayingMontage())
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void UNovaAbilityTask_MontageAndEvent::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (Ability && Ability->GetCurrentMontage() == MontageToPlay)
	{
		if (Montage == MontageToPlay)
		{
			AbilitySystemComponent->ClearAnimatingAbility(Ability);

			if (ShouldBroadcastAbilityTaskDelegates())
			{
				if (bInterrupted)
				{
					OnInterrupted.Broadcast(FGameplayTag(), FGameplayEventData());
				}
				else
				{
					OnBlendOut.Broadcast(FGameplayTag(), FGameplayEventData());
				}
			}
		}
	}
}

void UNovaAbilityTask_MontageAndEvent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCompleted.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}

	EndTask();
}

void UNovaAbilityTask_MontageAndEvent::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *Payload;
		TempData.EventTag = EventTag;

		EventReceived.Broadcast(EventTag, TempData);
	}
}

bool UNovaAbilityTask_MontageAndEvent::StopPlayingMontage()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo) return false;

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (AnimInstance == nullptr) return false;

	if (AbilitySystemComponent.IsValid() && Ability)
	{
		if (AbilitySystemComponent->GetAnimatingAbility() == Ability
			&& AbilitySystemComponent->GetCurrentMontage() == MontageToPlay)
		{
			FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageInstance)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}

			AbilitySystemComponent->CurrentMontageStop();
			return true;
		}
	}
	return false;
}

FString UNovaAbilityTask_MontageAndEvent::GetDebugString() const
{
	UAnimMontage* PlayingMontage = nullptr;
	if (Ability)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			PlayingMontage = AnimInstance->Montage_IsActive(MontageToPlay) ? MontageToPlay.Get() : Ability->GetCurrentMontage();
		}
	}

	return FString::Printf(TEXT("PlayMontageAndWaitForEvent. MontageToPlay: %s  (Currently Playing): %s"), *GetNameSafe(MontageToPlay), *GetNameSafe(PlayingMontage));
}