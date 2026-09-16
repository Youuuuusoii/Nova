// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../CharacterBase.h"
#include "MonsterBase.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API AMonsterBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AMonsterBase();

protected:
	bool	bIsActive;
	//BT/BB/ASC/Attribute

public:
	virtual void Tick(float DeltaTime) override;

	virtual void InitCharacterData(class UNovaCharacterData* CharacterData) override;

	bool IsMonsterActive() { return bIsActive; }
	void ActiveMonster();

protected:
	virtual void BeginPlay() override;
	void DeactiveMonster();
};
