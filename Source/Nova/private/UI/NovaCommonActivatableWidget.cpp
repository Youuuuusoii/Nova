// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NovaCommonActivatableWidget.h"

void UNovaCommonActivatableWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UNovaCommonActivatableWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	//Push되어 최상단에 올라올 때 호출
}

void UNovaCommonActivatableWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	//Pop되어 비활성화될 때 호출
}
