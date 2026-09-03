// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "NovaAttributeSetBase.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class NOVA_API UNovaAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UNovaAttributeSetBase();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data);
	//virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);
	//virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, Gold)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Exp;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, Exp)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, Level)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, Defense)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, CriticalChance)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData CriticalDamageRate;
	ATTRIBUTE_ACCESSORS(UNovaAttributeSetBase, CriticalDamageRate)

	
};
