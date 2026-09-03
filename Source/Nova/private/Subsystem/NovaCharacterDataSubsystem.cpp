// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/NovaCharacterDataSubsystem.h"
#include "Engine/AssetManager.h"
#include "Character/CharacterBase.h"
#include "Data/NovaCharacterData.h"

#include "NovaLogChannels.h"

UNovaCharacterDataSubsystem::UNovaCharacterDataSubsystem()
{
}

void UNovaCharacterDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UNovaCharacterDataSubsystem::LoadPlayerData()
{
	UAssetManager& AssetManager = UAssetManager::Get();

	TArray<FPrimaryAssetId>	CharacterAssetIds;

	AssetManager.GetPrimaryAssetIdList(FPrimaryAssetType("PlayerData"), CharacterAssetIds);

	if (CharacterAssetIds.IsEmpty())
	{
		LOG(TEXT("No Character Data Asset."));
		return;
	}

	TArray<FSoftObjectPath> Paths;
	for (const FPrimaryAssetId& Id : CharacterAssetIds)
	{
		Paths.Add(AssetManager.GetPrimaryAssetPath(Id));
	}

	// 동기 로딩
	UAssetManager::GetStreamableManager().RequestSyncLoad(Paths);

	for (const FPrimaryAssetId& AssetId : CharacterAssetIds)
	{
		UObject* LoadedObject = AssetManager.GetPrimaryAssetObject(AssetId);
		if (UNovaCharacterData* LoadedData = Cast<UNovaCharacterData>(LoadedObject))
		{
			LoadedPlayerDataArray.Add(LoadedData);
		}
	}
}

/*AssetManager.LoadPrimaryAssets(
	CharacterAssetIds,
	TArray<FName>(),
	FStreamableDelegate::CreateUObject(this, &UNovaCharacterDataSubsystem::OnPlayerDataLoaded, CharacterAssetIds)
);*/
