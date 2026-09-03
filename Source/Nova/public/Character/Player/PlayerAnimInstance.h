// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../CharacterAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Direction;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void CalculationPlayerDirection();
	
};
