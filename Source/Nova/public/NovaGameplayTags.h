// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace NovaGameplayTags
{
	NOVA_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);


	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputContext_Defualt);

	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UILayer_Game);
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UILayer_Menu);
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UILayer_Modal);

	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Trigger_ComboTagStart);
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Trigger_ComboTagEnd);
	
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Melee);
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_RMB);
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Skill1);
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Skill2);
	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Action_Ultimate);

	NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Event);

	// Declare all of the custom native tags that Lyra will use
	//NOVA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_IsDead);
	//LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Behavior_SurvivesDeath);
	//LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	//LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	//LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Death);
	//LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Damage);
	//LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Crouching);
	//LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	
	// These are mappings from MovementMode enums to GameplayTags associated with those enums (below)
	//LYRAGAME_API	extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	//LYRAGAME_API	extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

};
