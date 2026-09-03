// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NovaGA_SpawnActor.h"
#include "Ability/Actors/NovaAbilityActor.h"
#include "Character/CharacterBase.h"
#include "NovaGameplayTags.h"
#include "NovaLogChannels.h"

UNovaGA_SpawnActor::UNovaGA_SpawnActor()
{
}

void UNovaGA_SpawnActor::OnAbilityEvent(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::OnAbilityEvent(EventTag, EventData);

	if (EventTag == NovaGameplayTags::Ability_Event)
	{
		SpawnActor();
	}
}

void UNovaGA_SpawnActor::SpawnActor()
{
	UWorld* MyWorld = GetWorld();
	if (!MyWorld  || !AbilitySpawnActorClass)
	{
		LOG(TEXT("AbilitySpawnActorClass is nullptr"));

		return;
	}

	ACharacterBase* OwnerCharacter = GetCharacterBaseFromActorInfo();
	if (!OwnerCharacter)
	{
		return;
	}

	FTransform SpawnTransform = OwnerCharacter->GetActorTransform();

	FVector	SpawnPosition = ActorSpawnTransform.SpawnPoint + (OwnerCharacter->GetActorForwardVector() * ActorSpawnTransform.SpawnDistance);

	SpawnTransform.SetTranslation(SpawnPosition);

	FActorSpawnParameters	SpawnParam;
	SpawnParam.Owner = OwnerCharacter;
	SpawnParam.Instigator = OwnerCharacter;

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANovaAbilityActor* AbilityActor = MyWorld->SpawnActor<ANovaAbilityActor>(AbilitySpawnActorClass, SpawnTransform, SpawnParam);

	if (AbilityActor)
	{
		AbilityActor->ActivateAbilityActor(OwnerCharacter, FGameplayEffectSpecHandle());
	}
}
