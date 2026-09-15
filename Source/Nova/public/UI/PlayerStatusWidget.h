// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PlayerStatusWidget.generated.h"

/**
 * 
 */
struct FOnAttributeChangeData;

UCLASS()
class NOVA_API UPlayerStatusWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> HealthTextBlock;

	class UAbilitySystemComponent* AbilitySystemComponent;

public:
	void OnHealthChanged(const FOnAttributeChangeData& Data);

protected:
	void NativeConstruct() override;
	void UpdateHelathBar();

public:
	UFUNCTION()
	void BindPlayerStauts(class ANovaPlayerController* PlayerController ,class ANovaPlayerState* PlayerState);
};
