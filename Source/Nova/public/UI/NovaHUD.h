// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/NovaCommonActivatableWidget.h"
#include "NovaHUD.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UNovaHUD : public UNovaCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (WidgetBind))
	TObjectPtr<class UPlayerStatusWidget>	PlayerStatusWidget;

public:
	void NativeConstruct() override;

};
