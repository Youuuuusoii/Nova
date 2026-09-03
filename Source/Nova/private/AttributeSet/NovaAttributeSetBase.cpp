// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSet/NovaAttributeSetBase.h"
#include "GameplayEffectExtension.h"

UNovaAttributeSetBase::UNovaAttributeSetBase()
{
}

void UNovaAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
    }
}