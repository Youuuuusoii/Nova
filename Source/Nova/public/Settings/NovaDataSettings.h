// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NovaDataSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Nova UI Settings"))
class NOVA_API UNovaDataSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	FPrimaryAssetId UIDataAssetId = FPrimaryAssetId("UIData", "DA_UIData");
};
