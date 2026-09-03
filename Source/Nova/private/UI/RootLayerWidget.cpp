// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RootLayerWidget.h"

#include "UI/NovaCommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "NovaLogChannels.h"

void URootLayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LayerStacks.Add(NovaGameplayTags::UILayer_Game, Stack_Game);
	LayerStacks.Add(NovaGameplayTags::UILayer_Menu, Stack_Menu);
	LayerStacks.Add(NovaGameplayTags::UILayer_Modal, Stack_Modal);
}

UNovaCommonActivatableWidget* URootLayerWidget::PushWidget(const FGameplayTag& LayerTag, TSubclassOf<UNovaCommonActivatableWidget> WidgetClass)
{
	if (!WidgetClass)
	{
		LOG(TEXT("WidgetClass is nullptr"));
		return nullptr;
	}

	UCommonActivatableWidgetStack* TargetStack = GetLayerForTag(LayerTag);
	if (!TargetStack)
	{
		LOG(TEXT("TargetStack is nullptr"));
		return nullptr;
	}

	return TargetStack->AddWidget<UNovaCommonActivatableWidget>(WidgetClass);
}

bool URootLayerWidget::ClearWidgetStack(const FGameplayTag& LayerTag)
{
	if (UCommonActivatableWidgetStack* WidgetStack = GetLayerForTag(LayerTag))
	{
		WidgetStack->ClearWidgets();
		return true;
	}

	return false;
}

UCommonActivatableWidgetStack* URootLayerWidget::GetLayerForTag(const FGameplayTag& LayerTag)
{
	if (TObjectPtr< UCommonActivatableWidgetStack >* FoundStack = LayerStacks.Find(LayerTag))
	{
		return *FoundStack;
	}

	return nullptr;
}
