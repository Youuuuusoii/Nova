// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../NovaGameplayTags.h"
#include "NovaUIData.generated.h"

/**
 * 
 */

class UNovaCommonActivatableWidget;
class URootLayerWidget;

UCLASS()
class NOVA_API UNovaUIData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual FPrimaryAssetId	GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("UIData", GetFName());
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	TSubclassOf<URootLayerWidget>	RootWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TMap<FGameplayTag, TSubclassOf<UNovaCommonActivatableWidget>>	UIData;


public:
	TMap<FGameplayTag, TSubclassOf<UNovaCommonActivatableWidget>>& GetUIData() { return UIData; }
};
