// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Data/InputActionDataAsset.h"
#include "EnhancedInputComponent.h"
#include "../NovaGameplayTags.h"
#include "NovaEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UNovaEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	UNovaEnhancedInputComponent();

public:
	template<class UserClass, typename Function>
	void BindNativeInputAction(UInputActionDataAsset* InputData, FGameplayTag InputTag, ETriggerEvent eEvent, UserClass* User, Function FuncName);

	template<class UserClass, typename TriggetedFunction, typename CompletedFunction>
	void BindAbilityInputAction(UInputActionDataAsset* InputData, UserClass* User, TriggetedFunction TriggerFun, CompletedFunction CompletedFu);

};

template<class UserClass, typename Function>
inline void UNovaEnhancedInputComponent::BindNativeInputAction(UInputActionDataAsset* InputData, FGameplayTag InputTag, ETriggerEvent eEvent, UserClass* User, Function FuncName)
{
	check(InputData);

	if (const UInputAction* IA = InputData->FindNativeInputActionForTag(InputTag))
	{
		BindAction(IA, eEvent, User, FuncName);
	}
}

template<class UserClass, typename TriggetedFunction, typename CompletedFunction>
inline void UNovaEnhancedInputComponent::BindAbilityInputAction(UInputActionDataAsset* InputData, UserClass* User, TriggetedFunction TriggerFunc, CompletedFunction CompletedFunc)
{
	check(InputData);

	const TArray<FPlayerInputAction>& AbilityIAArray = InputData->GetAbilityInputActionArray();

	for (FPlayerInputAction Action : AbilityIAArray)
	{
		if (nullptr != Action.InputAction && Action.InputTag.IsValid())
		{
			if (TriggerFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, User, TriggerFunc, Action.InputTag);
			}

			if (CompletedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, User, CompletedFunc, Action.InputTag);
			}
		}
	}

}

