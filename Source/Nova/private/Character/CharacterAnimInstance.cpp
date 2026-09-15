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

	const FVector ActorLocation = CharacterPawn->GetActorLocation();

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
		WorldVelocity = FVector::ZeroVector;
		LocalVelocity = FVector::ZeroVector;
		return;
	}

	WorldVelocity = CharacterPawn->GetVelocity();
	WorldRotation = CharacterPawn->GetActorRotation();

	const FVector HorizontalVelocity = FVector(WorldVelocity.X, WorldVelocity.Y, 0.0f);

	LocalVelocity = WorldRotation.UnrotateVector(HorizontalVelocity);
}

void UCharacterAnimInstance::InAirState()
{
	bJumping = false;
	bFalling = false;
	bGround = false;
	bIsAcceleration = false;

	if (!OwnerCharacterMovement.IsValid())
	{
		return;
	}

	bGround = OwnerCharacterMovement->IsMovingOnGround();
	bIsAcceleration = !OwnerCharacterMovement->GetCurrentAcceleration().IsNearlyZero();

	if (OwnerCharacterMovement->IsFalling())
	{
		bJumping = WorldVelocity.Z > 0.f;
		bFalling = !bJumping;
	}

}
