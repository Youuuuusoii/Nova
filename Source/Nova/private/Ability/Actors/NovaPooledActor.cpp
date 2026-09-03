// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Actors/NovaPooledActor.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

// Sets default values
ANovaPooledActor::ANovaPooledActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(BoxComponent);

	StaticMeshComponent->SetupAttachment(BoxComponent);

	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void ANovaPooledActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANovaPooledActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANovaPooledActor::Activation()
{
	SetActorHiddenInGame(false);

	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ANovaPooledActor::Deactivate, LifeTime, true);
}

void ANovaPooledActor::Deactivate()
{
	SetActorHiddenInGame(true);

	GetWorldTimerManager().ClearTimer(LifeTimerHandle);
}

