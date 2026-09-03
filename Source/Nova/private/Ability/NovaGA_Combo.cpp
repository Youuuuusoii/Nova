// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NovaGA_Combo.h"

#include "Character/CharacterBase.h"
#include "Character/CharacterAnimInstance.h"

#include "NovaGameplayTags.h"
#include "NovaLogChannels.h"

UNovaGA_Combo::UNovaGA_Combo()
	:SectionID(0),
	bInputEvent(false)
{
}

void UNovaGA_Combo::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (bInputEvent)
	{
		if (CharacterAnim->Montage_IsPlaying(AbilityMontage))
		{
			int32 NextSectionID = SectionID + 1;

			if (AbilityMontage->CompositeSections.IsValidIndex(NextSectionID))
			{
				FName CurrentSectionName = CharacterAnim->Montage_GetCurrentSection();
				FName NextSectionName = AbilityMontage->CompositeSections[NextSectionID].SectionName;

				CharacterAnim->Montage_SetNextSection(CurrentSectionName, NextSectionName, AbilityMontage);

				bInputEvent = false;

				SectionID = NextSectionID;
			}
		}
	}
}

void UNovaGA_Combo::OnAbilityEvent(FGameplayTag EventTag, FGameplayEventData EventData)
{
	if (EventTag == NovaGameplayTags::Ability_Trigger_ComboTagStart)
	{
		bInputEvent = true;
	}
	
	if (EventTag == NovaGameplayTags::Ability_Trigger_ComboTagEnd)
	{
		bInputEvent = false;
	}
}

void UNovaGA_Combo::OnEndAbility()
{
	SectionID = 0;
	bInputEvent = false;

	Super::OnEndAbility();
}

void UNovaGA_Combo::InitAbility()
{
	if (!ActorInfoCharacter)
	{
		ActorInfoCharacter = GetCharacterBaseFromActorInfo();
	}

	if (!CharacterAnim && ActorInfoCharacter)
	{
		CharacterAnim = ActorInfoCharacter->GetCharacterAnimInstance();
	}

	Super::InitAbility();
}
