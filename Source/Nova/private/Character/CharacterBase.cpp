// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "Character/CharacterAnimInstance.h"

#include "AbilitySystemComponent.h"
#include "Ability/NovaGameplayAbility.h"
#include "GameplayTagContainer.h"

#include "Data/NovaAbilityData.h"

#include "NovaLogChannels.h"
#include "GameplayEffectTypes.h" 

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::InitAttribute(TSubclassOf<class UGameplayEffect> InitStatEffect)
{
	if (!AbilitySystemComponent || !AttributeSet || !InitStatEffect)
	{
		LOG(TEXT("ASC or Attri or Effect is null"));
		return;
	}

	FGameplayEffectContextHandle	EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddInstigator(this, this);

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitStatEffect, 1.0f, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void ACharacterBase::AddAbilities(UNovaAbilityData* AbilitiesData)
{
	if (!AbilitiesData || !AbilitySystemComponent)
	{
		return;
	}

	const TMap<FGameplayTag, TSubclassOf<UGameplayAbility>>	Abilities = AbilitiesData->GameplayAbilities;

	for (const auto& Ability : Abilities)
	{
		if (IsValid(Ability.Value.Get()))
		{
			if (UGameplayAbility* GA = Ability.Value->GetDefaultObject<UGameplayAbility>())
			{
				FGameplayAbilitySpec	AbilitySpec(GA, 1, INDEX_NONE, this);
				AbilitySpec.DynamicAbilityTags.AddTag(Ability.Key);

				AbilitySystemComponent->GiveAbility(AbilitySpec);
			}
		}
	}

}

void ACharacterBase::AddAbility(UNovaGameplayAbility* AbilityClass)
{
	if (!AbilityClass)
	{
		return;
	}

	FGameplayAbilitySpec AbilitySpec(AbilityClass, 1, INDEX_NONE, this);
	AbilitySystemComponent->GiveAbility(AbilitySpec);
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (CharacterAnimInstance.IsValid())
	{
		CharacterAnimInstance->InitializeCharacterAnimtaion(this);
	}	
}

void ACharacterBase::SetCharacterMesh(TSoftObjectPtr<USkeletalMesh> CharacterMeshObject)
{
	if (!CharacterMeshObject.IsValid())
	{
		LOG(TEXT("CharacterMesh is nullptr!"));
		return;
	}

	GetMesh()->SetSkeletalMeshAsset(CharacterMeshObject.Get());
}

void ACharacterBase::SetCharacterAnimInstance(TSoftClassPtr<UAnimInstance> CharacterAnimClass)
{
	if (CharacterAnimClass.IsNull())
	{
		LOG(TEXT("CharacterAnim is nullptr!"));
		return;
	}

	GetMesh()->SetAnimInstanceClass(CharacterAnimClass.Get());
}

UCharacterAnimInstance* ACharacterBase::GetCharacterAnimInstance()
{
	return CharacterAnimInstance.Get();
}

