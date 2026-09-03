// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "../NovaGameplayTags.h"
#include "RootLayerWidget.generated.h"

/**
 * 
 */
class UCommonActivatableWidgetStack;
class UNovaCommonActivatableWidget;

UCLASS()
class NOVA_API URootLayerWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(Transient)
    TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetStack>>   LayerStacks;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> Stack_Game;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> Stack_Menu;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> Stack_Modal;

public:
    UNovaCommonActivatableWidget* PushWidget(const FGameplayTag& LayerTag, TSubclassOf<UNovaCommonActivatableWidget> WidgetClass);
    bool ClearWidgetStack(const FGameplayTag& LayerTag);

private:
    UCommonActivatableWidgetStack* GetLayerForTag(const FGameplayTag& LayerTag);
	
};
