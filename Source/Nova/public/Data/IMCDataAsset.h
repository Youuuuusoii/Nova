// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../NovaGameplayTags.h"
#include "IMCDataAsset.generated.h"

/**
 * 
 */
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FIMCData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	Priority;
};

UCLASS()
class NOVA_API UIMCDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UIMCDataAsset();

	void AddMappingContext(const FGameplayTag& Tag, const ULocalPlayer* LocalPlayer) const;
	void RemoveMappingContext(const FGameplayTag& Tag, const ULocalPlayer* LocalPlayer) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, FIMCData>	InputMappingContext;
	
};
