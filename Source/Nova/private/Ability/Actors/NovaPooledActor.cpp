// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Actors/NovaPooledActor.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

// Sets default values
ANovaPooledActor::ANovaPooledActor()
	:bIsCollision(false)
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(BoxComponent);

	StaticMeshComponent->SetupAttachment(BoxComponent);

	SetActorHiddenInGame(true);
}

void ANovaPooledActor::BeginPlay()
{
	Super::BeginPlay();

	Deactivate();
}

void ANovaPooledActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANovaPooledActor::Activation()
{
	GetWorldTimerManager().ClearTimer(LifeTimerHandle);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(bIsCollision);

	if (LifeTime > 0.f)
	{
		GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ANovaPooledActor::Deactivate, LifeTime, false);
	}
}

void ANovaPooledActor::Deactivate()
{
	GetWorldTimerManager().ClearTimer(LifeTimerHandle);

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

