// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NovaGA_DirectionalSkill.h"
#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UNovaGA_DirectionalSkill::UNovaGA_DirectionalSkill()
{
}

void UNovaGA_DirectionalSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	CalculationActorDirection();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UNovaGA_DirectionalSkill::CalculationActorDirection()
{
	ACharacterBase* CharacterBase = GetCharacterBaseFromActorInfo();
	
	if(!CharacterBase)
	{
		OnEndAbility();
		return;
	}

	FVector InputVector = CharacterBase->GetCharacterMovement()->GetLastInputVector();

	FName SectionName = FName("Fwd");

	if (InputVector.IsNearlyZero())
	{
		PlaySectionName = SectionName;
		Direction = CharacterBase->GetActorForwardVector();
		return;
	}

	FVector ActorForwrad = CharacterBase->GetActorForwardVector();
	FVector ActorRight= CharacterBase->GetActorRightVector();

	float ForwardDot = FVector::DotProduct(ActorForwrad, InputVector);
	float RightDot = FVector::DotProduct(ActorRight, InputVector);

	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
	{
		if (ForwardDot > 0.f)
		{
			SectionName = FName("Fwd");
			Direction = CharacterBase->GetActorForwardVector();
		}
		else
		{
			SectionName = FName("Bwd");
			Direction = CharacterBase->GetActorForwardVector()  * -1.f;
		}
	}
	else
	{
		if (RightDot > 0.f)
		{
			SectionName = FName("Right");
			Direction = CharacterBase->GetActorRightVector();
		}
		else
		{
			SectionName = FName("Left");
			Direction = CharacterBase->GetActorRightVector() * -1.f;
		}
	}

	PlaySectionName = SectionName;
}
