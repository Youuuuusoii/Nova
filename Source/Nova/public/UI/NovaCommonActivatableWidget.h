// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "../NovaGameplayTags.h"
#include "NovaCommonActivatableWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EUIOpenType : uint8
{
	Stack,
	ClearAndShow
};

UCLASS()
class NOVA_API UNovaCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EUIOpenType	OpenType;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Layers")
	FGameplayTag LayerTag;

public:
	void NativeOnInitialized() override;
	void NativeOnActivated()	override;
	void NativeOnDeactivated() override;	

	const FGameplayTag& GetLayerTag() const { return LayerTag; }
	EUIOpenType GetOpenType() const { return OpenType; }

	/*
	GetDesiredInputConfig()	입력 설정
	GetDesiredFocusTarget()	방향키/게임패드/조이스틱이 가장 먼저 가리키고 있어야할 첫번째 버튼 지정
	*/
};
