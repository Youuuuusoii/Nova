// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DecalComponent.h"
#include "NovaDecalComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Nova), meta = (BlueprintSpawnableComponent))
class NOVA_API UNovaDecalComponent : public UDecalComponent
{
	GENERATED_BODY()
	
public:
	UNovaDecalComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Mova|Decal Settings")
	TObjectPtr<UMaterialInterface> NovaDecalMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Mova|Decal Settings")
	FVector	NovaDecalSize;

	UPROPERTY(EditDefaultsOnly, Category = "Mova|Decal Settings")
	float	FadeOutDuration = 0.f;

	FTimerHandle DecalTimerHandle;

public:
	UFUNCTION(BlueprintCallable)
	void PlayDecal(FVector Location, FRotator Rotation, float LifeTime);

	void StopDecal();

};
