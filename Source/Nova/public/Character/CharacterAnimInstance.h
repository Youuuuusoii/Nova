// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
class UCharacterMovementComponent;

UCLASS()
class NOVA_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCharacterAnimInstance();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bIsAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bGround;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	LocationSpeed;

	UPROPERTY()
	TWeakObjectPtr<ACharacter> CharacterPawn;

	UPROPERTY()
	TWeakObjectPtr<UCharacterMovementComponent>	OwnerCharacterMovement;

	FVector		WorldLocation;
	FVector		LocalVelocity;
	FVector		WorldVelocity;
	FRotator	WorldRotation;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void InitializeCharacterAnimtaion(ACharacter* InCharacter);

protected:
	void UpdateLocationData(float DeltaSeconds);
	void UpdateVelocityData();
	void InAirState();
};
