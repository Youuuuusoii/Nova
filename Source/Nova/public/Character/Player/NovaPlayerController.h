// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NovaPlayerController.generated.h"

/**
 * 
 */

class UIMCDataAsset;
class ANovaPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStateReady,ANovaPlayerController*, NovaPlayerController, ANovaPlayerState*, NovaPlayerState);

UCLASS()
class NOVA_API ANovaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANovaPlayerController();
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateReady OnPlayerStateReady;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMC")
	UIMCDataAsset* IMCData;

	TObjectPtr<class UNovaAbilitySystemComponent>	NovaAbilitySystemComponent;

protected:
	virtual void BeginPlay() override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	//UFUNCTION(BlueprintCallable)
	//void AddMappingContext(const FGameplayTag& ContextTag) const;

	//UFUNCTION(BlueprintCallable)
	//void RemoveMappingContext(const FGameplayTag& ContextTag) const;
};
