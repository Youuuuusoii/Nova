// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Actors/NovaAbilityActor.h"
#include "GameplayEffectTypes.h"

ANovaAbilityActor::ANovaAbilityActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AbilityMesh"));

	RootComponent = MeshComponent;
}

void ANovaAbilityActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (LifeTime > 0.f)
	{
		SetLifeSpan(LifeTime);
	}
}

void ANovaAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANovaAbilityActor::ActivateAbilityActor(AActor* AbilityActorInstigator, FGameplayEffectSpecHandle DamangeSpec)
{

}
