// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/NovaDecalComponent.h"
#include "TimerManager.h"

UNovaDecalComponent::UNovaDecalComponent()
{

}

void UNovaDecalComponent::PlayDecal(FVector Location, FRotator Rotation, float LifeTime)
{
	SetWorldLocationAndRotation(Location, Rotation);
	DecalSize = NovaDecalSize;

	if (FadeOutDuration > 0.f)
	{
		float StartDelay = FMath::Max(0.f, LifeTime - FadeOutDuration);

		SetFadeOut(StartDelay, FadeOutDuration, false);
	}
	else
	{
		SetFadeOut(0.f, 0.f, false);
	}

	SetVisibility(true);

	GetWorld()->GetTimerManager().SetTimer(DecalTimerHandle, this, &UNovaDecalComponent::StopDecal, LifeTime, false);
}

void UNovaDecalComponent::StopDecal()
{
	SetVisibility(false);

	GetWorld()->GetTimerManager().ClearTimer(DecalTimerHandle);
}
