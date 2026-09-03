// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NovaCharacterData.generated.h"

/**
 * 
 */

class ACharacterBase;

UCLASS()
class NOVA_API UNovaCharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual FPrimaryAssetId	GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("CharacterData", GetFName());
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftClassPtr<ACharacterBase> CharacterPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftObjectPtr<USkeletalMesh> CharacterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftClassPtr<UAnimInstance> CharacterAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TSubclassOf<class UGameplayEffect> InitStatEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<class UNovaAbilityData> CharacterAbility;
};
