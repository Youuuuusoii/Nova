// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../NovaGameplayTags.h"
#include "InputActionDataAsset.generated.h"

/**
 * 
 */

class UInputAction;

USTRUCT(BlueprintType)
struct FPlayerInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag	InputTag;
};

UCLASS()
class NOVA_API UInputActionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UInputActionDataAsset();

	const UInputAction* FindNativeInputActionForTag(FGameplayTag Tag);
	const TArray<FPlayerInputAction>& GetAbilityInputActionArray() { return AbilityInputAction; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputAction")
	TArray<FPlayerInputAction>	NativeInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputAction")
	TArray<FPlayerInputAction>	AbilityInputAction;
};
