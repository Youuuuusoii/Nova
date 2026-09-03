// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerAnimInstance.h"

#include "GameFramework/Character.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CalculationPlayerDirection();
}

void UPlayerAnimInstance::CalculationPlayerDirection()
{
	if (CharacterPawn.IsValid() && LocationSpeed > 0.f)
	{
		FVector Velocity = CharacterPawn->GetVelocity();

		if (!Velocity.IsNearlyZero())
		{
			FVector	PlayerLocalVelocity = CharacterPawn->GetActorTransform().InverseTransformVectorNoScale(CharacterPawn->GetVelocity());	//로컬 변환
			Direction = PlayerLocalVelocity.Rotation().Yaw;
		}
	}
}
