// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NovaPooledActor.generated.h"

class UBoxComponent;

UCLASS()
class NOVA_API ANovaPooledActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANovaPooledActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Nova|Setting")
	bool bIsCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Nova|Setting")
	float	LifeTime;

	FTimerHandle	LifeTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activation();

	UFUNCTION()
	void Deactivate();
};
