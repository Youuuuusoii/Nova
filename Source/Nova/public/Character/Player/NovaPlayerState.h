// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "NovaPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API ANovaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANovaPlayerState();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UNovaAbilitySystemComponent>	AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UNovaAttributeSetBase>	AttributeSet;

public:
	class UAbilitySystemComponent* GetAbilitySystemComponent() const;
	class UAttributeSet* GetAttributeSet() const;
};
