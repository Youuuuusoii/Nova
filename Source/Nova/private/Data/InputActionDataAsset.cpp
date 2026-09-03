// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputActionDataAsset.h"

UInputActionDataAsset::UInputActionDataAsset()
{
}

const UInputAction* UInputActionDataAsset::FindNativeInputActionForTag(FGameplayTag Tag)
{
    for (FPlayerInputAction& IA : NativeInputAction)
    {
        if (IA.InputAction != nullptr && IA.InputTag == Tag)
        {
            return IA.InputAction;
        }
    }

    return nullptr;
}
