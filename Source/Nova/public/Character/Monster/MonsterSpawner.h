// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

class UNovaMonsterData;
class AMonsterBase;

UCLASS()
class NOVA_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonsterSpawner();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TObjectPtr<UNovaMonsterData>	SpawnMonsterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32	SpawnMonsterCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32	SpawnInterval;

private:
	TArray<TObjectPtr<AMonsterBase>>	 SpawnMonsters;

	FTimerHandle	SpawnTimerHandle;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void MonsterRespawn();

private:
	void InitSpawnMonsters();

};
