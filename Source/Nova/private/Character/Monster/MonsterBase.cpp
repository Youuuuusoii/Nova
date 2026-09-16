// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterBase.h"
#include "Data/NovaMonsterData.h"

AMonsterBase::AMonsterBase()
	:bIsActive(false)
{
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
}



void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterBase::InitCharacterData(UNovaCharacterData* CharacterData)
{
	Super::InitCharacterData(CharacterData);
	

	DeactiveMonster();
	//BT/BB 등등
}

void AMonsterBase::ActiveMonster()
{
	bIsActive = true;
	//몬스터가 활성화 될 때 설정해야할 것들
}

void AMonsterBase::DeactiveMonster()
{
	bIsActive = false;
}