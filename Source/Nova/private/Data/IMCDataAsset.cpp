// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/IMCDataAsset.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

UIMCDataAsset::UIMCDataAsset()
{
}

void UIMCDataAsset::AddMappingContext(const FGameplayTag& Tag, const ULocalPlayer* LocalPlayer) const
{
	check(LocalPlayer);

	if (const FIMCData* IMCData = InputMappingContext.Find(Tag))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (IMCData->IMC && !SubSystem->HasMappingContext(IMCData->IMC))
			{
				SubSystem->AddMappingContext(IMCData->IMC, IMCData->Priority);
			}
		}
	}
}

void UIMCDataAsset::RemoveMappingContext(const FGameplayTag& Tag, const ULocalPlayer* LocalPlayer) const
{
	check(LocalPlayer);

	if (const FIMCData* IMCData = InputMappingContext.Find(Tag))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (IMCData->IMC && SubSystem->HasMappingContext(IMCData->IMC))
			{
				SubSystem->RemoveMappingContext(IMCData->IMC);
			}
		}
	}
}
