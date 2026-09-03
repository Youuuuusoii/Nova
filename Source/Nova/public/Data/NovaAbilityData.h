// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagsManager.h"
#include "NovaAbilityData.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UNovaAbilityData : public UDataAsset
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSubclassOf<class UGameplayAbility>>	GameplayAbilities;
	//수정예정
};
