// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NovaDefaultGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API ANovaDefaultGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANovaDefaultGameModeBase();
	
	void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	void OnPlayerClassLoaded(APlayerController* PlayerController);
};
