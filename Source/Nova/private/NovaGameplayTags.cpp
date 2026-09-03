// Fill out your copyright notice in the Description page of Project Settings.


#include "NovaGameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"
#include "NovaLogChannels.h"

namespace NovaGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "Input.Move", "Move Input.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputContext_Defualt, "Input.Context.Default", "Base input context for the player character.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UILayer_Game, "UI.Layer.Game", "Base layer for standard gameplay HUD. Does not consume input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UILayer_Menu, "UI.Layer.Menu", "Middle layer for interactive menus. Blocks gameplay input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UILayer_Modal, "UI.Layer.Modal", "Top layer for critical popups.Blocks all input to lower layers.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Trigger_ComboTagStart, "Ability.Combo.Start", "Ability Combo Type - Start Tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Trigger_ComboTagEnd, "Ability.Combo.End", "Ability Combo Type - End Tag.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Action_Melee, "Ability.Action.Melee", "Character Melee Ability Tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Action_RMB, "Ability.Action.RMB", "Character RMB Ability Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Action_Skill1, "Ability.Action.Skill1", "Character Skill1 Ability Tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Action_Skill2, "Ability.Action.Skill2", "Character Skill2 Ability Tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Action_Ultimate, "Ability.Action.Ultimate", "Character Ultimate Ability Tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event, "Ability.Event", "Ability Event Trigger Tag.");

	NOVA_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& TagManger = UGameplayTagsManager::Get();
		FGameplayTag FoundTag = TagManger.RequestGameplayTag(FName(*TagString), false);

		if (!FoundTag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			TagManger.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					LOG(TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
					FoundTag = TestTag;
					break;
				}
			}
		}

		return FoundTag;
	}
}
