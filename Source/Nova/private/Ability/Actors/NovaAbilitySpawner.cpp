// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Actors/NovaAbilitySpawner.h"
#include "Ability/Actors/NovaPooledActor.h"
#include "GameplayEffectTypes.h"
#include "TimerManager.h"

#include "NovaLogChannels.h"

ANovaAbilitySpawner::ANovaAbilitySpawner()
{
}

void ANovaAbilitySpawner::BeginPlay()
{
	Super::BeginPlay();

	UWorld* MyWorld = GetWorld();
	if (PooledActorClass && MyWorld)
	{
		for (int32 i = 0; i < ActorCount; ++i)
		{
			ANovaPooledActor* NewActor = MyWorld->SpawnActor<ANovaPooledActor>(PooledActorClass, FVector::ZeroVector, FRotator::ZeroRotator);

			if (NewActor)
			{
				PooledActors.Add(NewActor);
			}
		}
	}
}

void ANovaAbilitySpawner::ActivateAbilityActor(AActor* AbilityActorInstigator, FGameplayEffectSpecHandle DamangeSpec)
{
	SpawnInstigator = AbilityActorInstigator;

	BP_PooledActorSetTransform();

	if (EActorSpawnType::Immediate == SpawnType)
	{
		ImmediateSpawnActors();
	}
	else if(EActorSpawnType::Delayed == SpawnType)
	{
		CurrentSpawnIndex = 0;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ANovaAbilitySpawner::ProcessNextSpawn, SpawnInterval, true);
	}

}

void ANovaAbilitySpawner::ImmediateSpawnActors()
{
	for (int32 Index = 0; Index < ActorCount; ++Index)
	{
		if (!PooledActors.IsValidIndex(Index) || !SpawnActorsTransform.IsValidIndex(Index))
		{
			return;
		}

		ANovaPooledActor* PooledActor = PooledActors[Index];

		if (PooledActor)
		{
			PooledActor->SetActorTransform(SpawnActorsTransform[Index]);
			PooledActor->Activation();
		}
	}

	SetActorHiddenInGame(true);
}

void ANovaAbilitySpawner::ProcessNextSpawn()
{
	if (CurrentSpawnIndex >= SpawnActorsTransform.Num())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SetActorHiddenInGame(true);
		return;
	}

	if(!PooledActors.IsValidIndex(CurrentSpawnIndex) ||	!SpawnActorsTransform.IsValidIndex(CurrentSpawnIndex))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SetActorHiddenInGame(true);

		LOG(TEXT("PooledActors IsValideIndex : %s"), PooledActors.IsValidIndex(CurrentSpawnIndex) ? TEXT("true") : TEXT("false"));
		LOG(TEXT("SpawnActorsTransform IsValideIndex : %s"), SpawnActorsTransform.IsValidIndex(CurrentSpawnIndex) ? TEXT("true") : TEXT("false"));
		return;
	}

	ANovaPooledActor* PooledActor = PooledActors[CurrentSpawnIndex];
	if (PooledActor)
	{
		PooledActor->SetActorTransform(SpawnActorsTransform[CurrentSpawnIndex]);
		PooledActor->Activation();

	}
	else
	{
		LOG(TEXT("PooledActor is nullptr Index : : %d"), CurrentSpawnIndex);
	}

	++CurrentSpawnIndex;
}
