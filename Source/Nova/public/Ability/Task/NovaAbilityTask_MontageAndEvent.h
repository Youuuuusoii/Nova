// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "NovaAbilityTask_MontageAndEvent.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNovaMontageAndEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

UCLASS()
class NOVA_API UNovaAbilityTask_MontageAndEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	UNovaAbilityTask_MontageAndEvent();

	UPROPERTY(BlueprintAssignable)
	FNovaMontageAndEventDelegate	OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FNovaMontageAndEventDelegate	OnBlendOut;

	UPROPERTY(BlueprintAssignable)
	FNovaMontageAndEventDelegate OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FNovaMontageAndEventDelegate OnCancelled;

	// 애니메이션 노티파이 등에서 날아온 이벤트를 받는 델리게이트
	UPROPERTY(BlueprintAssignable)
	FNovaMontageAndEventDelegate EventReceived;

	// 태스크 생성용 스태틱 팩토리 함수
	UFUNCTION(BlueprintCallable, Category = "Nova|Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UNovaAbilityTask_MontageAndEvent* PlayMontageAndWaitForEvent(UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		FGameplayTagContainer EventTags,
		float Rate = 1.f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.f);

	UFUNCTION()
	void OnAbilityCancelled();

	UFUNCTION()
	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

protected:
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;

	bool StopPlayingMontage();
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

private:
	UPROPERTY()
	TObjectPtr<UAnimMontage> MontageToPlay;

	FGameplayTagContainer EventTags;
	float Rate;
	FName StartSection;
	float AnimRootMotionTranslationScale;
	bool bStopWhenAbilityEnds;

	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;
	
};
