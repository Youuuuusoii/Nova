// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "../NovaGameplayTags.h"
#include "NovaUIManagerSubsystem.generated.h"

/**
 * 
 */

class UNovaCommonActivatableWidget;
class URootLayerWidget;

UCLASS()
class NOVA_API UNovaUIManagerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	UNovaUIManagerSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	UPROPERTY()
	TMap<FGameplayTag, TSubclassOf<UNovaCommonActivatableWidget>> WidgetClasses;

	UPROPERTY()
	TSubclassOf<URootLayerWidget> RootWidgetClass;

	UPROPERTY()
	TObjectPtr<URootLayerWidget>	RootWidget;

public:
	void LoadUIData();
	void CreateRootWidget(APlayerController* PlayerController);
	void StackCommonWidget(const FGameplayTag& UITag, APlayerController* PlayerController);

protected:
	const TSubclassOf<UNovaCommonActivatableWidget> FindWidgetClass(const FGameplayTag& WidgetTag);
};
