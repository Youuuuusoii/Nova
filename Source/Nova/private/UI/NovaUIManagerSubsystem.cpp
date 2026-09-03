// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NovaUIManagerSubsystem.h"
#include "UI/NovaCommonActivatableWidget.h"
#include "UI/RootLayerWidget.h"
#include "Engine/AssetManager.h"
#include "Data/NovaUIData.h"
#include "Settings/NovaDataSettings.h"

#include "NovaLogChannels.h"

UNovaUIManagerSubsystem::UNovaUIManagerSubsystem()
{
}

void UNovaUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadUIData();
}

void UNovaUIManagerSubsystem::LoadUIData()
{
	UAssetManager& AssetManager = UAssetManager::Get();

	const UNovaDataSettings* DataSettings = GetDefault<UNovaDataSettings>();

	FPrimaryAssetId AssetID = DataSettings->UIDataAssetId;

	const FSoftObjectPath Path = AssetManager.GetPrimaryAssetPath(AssetID);

	// 동기 로딩
	UAssetManager::GetStreamableManager().RequestSyncLoad(Path);

	UObject* LoadedObject = AssetManager.GetPrimaryAssetObject(AssetID);
	if (UNovaUIData* LoadedData = Cast<UNovaUIData>(LoadedObject))
	{
		RootWidgetClass = LoadedData->RootWidget;
		WidgetClasses = LoadedData->GetUIData();
	}
}

const TSubclassOf<UNovaCommonActivatableWidget> UNovaUIManagerSubsystem::FindWidgetClass(const FGameplayTag& WidgetTag)
{
	if (const TSubclassOf<UNovaCommonActivatableWidget>* FoundWidgetClass = WidgetClasses.Find(WidgetTag))
	{
		return *(FoundWidgetClass);
	}
	
	return nullptr;
}

void UNovaUIManagerSubsystem::CreateRootWidget(APlayerController* PlayerController)
{
	if (!PlayerController || !RootWidgetClass || RootWidget)
	{	
		return;
	}

	RootWidget = CreateWidget<URootLayerWidget>(PlayerController, RootWidgetClass);

	if (RootWidget)
	{
		RootWidget->AddToPlayerScreen();
	}
}

void UNovaUIManagerSubsystem::StackCommonWidget(const FGameplayTag& UITag, APlayerController* PlayerController)
{
	if (!PlayerController || !RootWidget)
	{
		return;
	}

	TSubclassOf<UNovaCommonActivatableWidget> WidgetClass = FindWidgetClass(UITag);
	
	if (!WidgetClass)
	{
		LOG(TEXT("Widget Class not found"));
		return;
	}

	UNovaCommonActivatableWidget* Widget = WidgetClass.GetDefaultObject();

	if (!Widget)
	{
		LOG(TEXT("Widget DefaultObject is nullptr"));
		return;
	}

	FGameplayTag WidgetLayerTag = Widget->GetLayerTag();
	if (EUIOpenType::ClearAndShow == Widget->GetOpenType())
	{
		RootWidget->ClearWidgetStack(WidgetLayerTag);
	}

	if (WidgetClass)
	{
	
		RootWidget->PushWidget(WidgetLayerTag, WidgetClass);
	}
}
