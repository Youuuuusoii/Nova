// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UCharacterAnimInstance::UCharacterAnimInstance()
	: bJumping(false)
	, bFalling(false)
	, bGround(true)
{
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateVelocityData();
	UpdateLocationData(DeltaSeconds);
	InAirState();
}

void UCharacterAnimInstance::InitializeCharacterAnimtaion(ACharacter* InCharacter)
{
	CharacterPawn = InCharacter;

	if (CharacterPawn.IsValid())
	{
		OwnerCharacterMovement = CharacterPawn->GetCharacterMovement();

		WorldLocation = CharacterPawn->GetActorLocation();
		WorldRotation = CharacterPawn->GetActorRotation();
	}
}

void UCharacterAnimInstance::UpdateLocationData(float DeltaSeconds)
{
	if (!CharacterPawn.IsValid())
	{
		return;
	}

	FVector ActorLocation = CharacterPawn->GetActorLocation();

	FVector CurrentLocation = ActorLocation - WorldLocation;
	CurrentLocation.Z = 0.f;

	//거리확인
	const float LastLocationLength = CurrentLocation.Length();

	if (!FMath::IsNearlyZero(DeltaSeconds))
	{
		LocationSpeed = LastLocationLength / DeltaSeconds;
	}
	else
	{
		LocationSpeed = 0.f;
	}

	WorldLocation = ActorLocation;
}

void UCharacterAnimInstance::UpdateVelocityData()
{
	if (!CharacterPawn.IsValid())
	{
		return;
	}

	WorldVelocity = CharacterPawn->GetVelocity();

	FVector WorldVelocity2D = WorldVelocity * FVector(1.0f, 1.0f, 0.0f);

	LocalVelocity = WorldRotation.UnrotateVector(WorldVelocity2D);
}

void UCharacterAnimInstance::InAirState()
{
	bJumping = bFalling = false;

	if (!OwnerCharacterMovement.IsValid())
	{
		return;
	}

	FVector Acceleration = OwnerCharacterMovement->GetCurrentAcceleration();

	bIsAcceleration = (Acceleration.SquaredLength() > 0.f);

	if (EMovementMode::MOVE_Falling == OwnerCharacterMovement->MovementMode)
	{
		if (WorldVelocity.Z > 0.f)
		{
			bJumping = true;
		}
		else
		{
			bFalling = true;
		}
	}

}
