// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

class UCharacterAnimInstance;

UCLASS()
class NOVA_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	UPROPERTY()
	TWeakObjectPtr<UCharacterAnimInstance>	CharacterAnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAttributeSet> AttributeSet;

public:	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

	virtual void InitCharacterData(class UNovaCharacterData* CharacterData);

	void SetCharacterMesh(TSoftObjectPtr<USkeletalMesh> CharacterMeshObject);
	void SetCharacterAnimInstance(TSoftClassPtr<UAnimInstance> CharacterAnimClass);

	class UCharacterAnimInstance* GetCharacterAnimInstance();

protected:
	virtual void BeginPlay() override;
	void InitAttribute(TSubclassOf<class UGameplayEffect> InitStatEffect);
	void AddAbilities(class UNovaAbilityData* AbilitiesData);
	void AddAbility(class UNovaGameplayAbility* AbilityClass);
};
