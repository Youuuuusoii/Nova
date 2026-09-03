// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NovaANS_SendGameplayEvent.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"

UNovaANS_SendGameplayEvent::UNovaANS_SendGameplayEvent()
{
}

void UNovaANS_SendGameplayEvent::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp || !MeshComp->GetOwner()) return;

	AActor* OwnerActor = MeshComp->GetOwner();

	FGameplayEventData Payload;
	Payload.EventTag = BeginEventTag;
	Payload.Instigator = OwnerActor;
	Payload.Target = OwnerActor;

	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, BeginEventTag, Payload);
}

void UNovaANS_SendGameplayEvent::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp || !MeshComp->GetOwner()) return;

	AActor* OwnerActor = MeshComp->GetOwner();


	FGameplayEventData Payload;
	Payload.EventTag = EndEventTag;
	Payload.Instigator = OwnerActor;
	Payload.Target = OwnerActor;


	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EndEventTag, Payload);
}
