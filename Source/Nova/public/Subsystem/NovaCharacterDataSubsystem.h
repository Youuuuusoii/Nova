// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NovaCharacterDataSubsystem.generated.h"

/**
 * 
 */
class UNovaCharacterData;

UCLASS()
class NOVA_API UNovaCharacterDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UNovaCharacterDataSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY()
	TArray<TObjectPtr<UNovaCharacterData>> LoadedPlayerDataArray;

//protected:
	void LoadPlayerData();
};
