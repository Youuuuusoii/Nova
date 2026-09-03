// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/NovaPlayerController.h"

#include "Ability/NovaAbilitySystemComponent.h"
#include "Component/NovaEnhancedInputComponent.h"
#include "UI/NovaUIManagerSubsystem.h"
#include "Character/Player/PlayerBase.h"
#include "Character/Player/NovaPlayerState.h"
#include "Data/IMCDataAsset.h"

#include "NovaGameplayTags.h"

ANovaPlayerController::ANovaPlayerController()
{
}

void ANovaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IMCData)
	{
		IMCData->AddMappingContext(NovaGameplayTags::InputContext_Defualt, GetLocalPlayer());
	}

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UNovaUIManagerSubsystem* UIManager = LocalPlayer->GetSubsystem<UNovaUIManagerSubsystem>())
		{
			UIManager->CreateRootWidget(this);
			UIManager->StackCommonWidget(NovaGameplayTags::UILayer_Game, this);
		}
	}

	if (ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(GetPawn()))
	{
		NovaAbilitySystemComponent = Cast<UNovaAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent());
	}
}

void ANovaPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	if (NovaAbilitySystemComponent)
	{
		NovaAbilitySystemComponent->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
}

void ANovaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANovaPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (ANovaPlayerState* PS = Cast<ANovaPlayerState>(PlayerState))
	{
		if (PS->GetAbilitySystemComponent())
		{
			OnPlayerStateReady.Broadcast(this, PS);
		}
	}
}

void ANovaPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
