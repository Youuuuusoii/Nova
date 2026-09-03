// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/NovaCharacterData.h"
#include "NovaPlayerData.generated.h"

/**
 * 
 */
class UInputActionDataAsset;

UCLASS()
class NOVA_API UNovaPlayerData : public UNovaCharacterData
{
	GENERATED_BODY()
	
public:
	virtual FPrimaryAssetId	GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("PlayerData", GetFName());
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IA")
	UInputActionDataAsset* InputData;
};
