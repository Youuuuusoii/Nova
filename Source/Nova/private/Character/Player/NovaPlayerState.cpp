// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/NovaPlayerState.h"
#include "Ability/NovaAbilitySystemComponent.h"
#include "AttributeSet/NovaAttributeSetBase.h"

ANovaPlayerState::ANovaPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject< UNovaAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UNovaAttributeSetBase>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ANovaPlayerState::GetAbilitySystemComponent()	const
{
	return AbilitySystemComponent;
}

UAttributeSet* ANovaPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}