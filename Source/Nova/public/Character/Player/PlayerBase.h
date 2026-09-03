// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../CharacterBase.h"
#include "PlayerBase.generated.h"

/**
 * 
 */
struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class NOVA_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCamera")
	class USpringArmComponent* PlayerSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCamera")
	class UCameraComponent* PlayerMainCamera;

	TObjectPtr<class UNovaAbilitySystemComponent>	NovaAbilitySystemComponent;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitCharacterData(class UNovaCharacterData* PlayerData);
	
	void Input_Move(const FInputActionValue& IAValue);
	void Input_AbilityTriggered(FGameplayTag InputTag);
	void Input_AbilityCompleted(FGameplayTag InputTag);

	class UNovaAbilitySystemComponent* GetNovaAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;


};
