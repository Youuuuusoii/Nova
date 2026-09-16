// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterSpawner.h"
#include "Data/NovaMonsterData.h"
#include "Character/Monster/MonsterBase.h"
#include "TimerManager.h"

#include "NovaLogChannels.h"

AMonsterSpawner::AMonsterSpawner()
	:SpawnMonsterCount(0)
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

	InitSpawnMonsters();
}

void AMonsterSpawner::MonsterRespawn()
{
	if (SpawnMonsterCount <= 0)
	{
		LOG(TEXT("Monster Spawn CountNum is zero"));
		return;
	}

	if (!SpawnMonsterData || SpawnMonsterData->CharacterPawn.IsNull())
	{
		LOG(TEXT("Monster Data / class is nullptr"));
		return;
	}

	for (int32 Index = 0; Index < SpawnMonsterCount; ++Index)
	{
		if (!SpawnMonsters.IsValidIndex(Index))
		{
			break;
		}

		AMonsterBase* Monster = SpawnMonsters[Index];

		if (Monster && !Monster->IsMonsterActive())
		{
			Monster->ActiveMonster();
		}
	}
}

void AMonsterSpawner::InitSpawnMonsters()
{
	if (SpawnMonsterCount <= 0)
	{
		LOG(TEXT("Monster Spawn CountNum is zero"));
		return;
	}

	if (!SpawnMonsterData || SpawnMonsterData->CharacterPawn.IsNull())
	{
		LOG(TEXT("Monster Data / class is nullptr"));
		return;
	}

	SpawnMonsters.Empty();

	UClass* LoadedClass = SpawnMonsterData->CharacterPawn.LoadSynchronous();

	if (LoadedClass)
	{
		for (int32 Index = 0; Index < SpawnMonsterCount; ++Index)
		{
			/*
			위치는 스포너의 위치에서 랜덤으로 
			*/
			if (AMonsterBase* MonsterPawn = GetWorld()->SpawnActor<AMonsterBase>(LoadedClass, GetActorTransform()))
			{
				MonsterPawn->InitCharacterData(SpawnMonsterData);
				SpawnMonsters.Add(MonsterPawn);
			}
		}
	}
	else
	{
		LOG(TEXT("Monster Class Loaded Failed!"));
		return;
	}

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AMonsterSpawner::MonsterRespawn, SpawnInterval, true);
}

