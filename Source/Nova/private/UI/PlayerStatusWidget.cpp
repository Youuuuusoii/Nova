// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerStatusWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "AbilitySystemComponent.h"
#include "Character/Player/NovaPlayerState.h"
#include "Character/Player/NovaPlayerController.h"
#include "AttributeSet/NovaAttributeSetBase.h"

#include "NovaLogChannels.h"

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ANovaPlayerController* NovaController = Cast<ANovaPlayerController>(GetOwningPlayer()))
	{
		if (ANovaPlayerState* NovaPS = Cast<ANovaPlayerState>(NovaController->PlayerState))
		{
			BindPlayerStauts(NovaController, NovaPS);
		}
		else
		{
			NovaController->OnPlayerStateReady.AddDynamic(this, &UPlayerStatusWidget::BindPlayerStauts);
		}
	}
	else
	{
		LOG(TEXT("PlayerController is nullptr"));
	}
}

void UPlayerStatusWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	UpdateHelathBar();
}
void UPlayerStatusWidget::UpdateHelathBar()
{
	if (!AbilitySystemComponent || !HealthProgressBar || !HealthTextBlock)
	{
		return;
	}

	float CurrentMaxHealth = AbilitySystemComponent->GetNumericAttribute(UNovaAttributeSetBase::GetMaxHealthAttribute());
	float CurrentHealth = AbilitySystemComponent->GetNumericAttribute(UNovaAttributeSetBase::GetHealthAttribute());

	if (CurrentMaxHealth > 0.f)
	{
		float HealthPercent = CurrentHealth / CurrentMaxHealth;
		HealthProgressBar->SetPercent(HealthPercent);
	}

	//반올림
	int32 Health = FMath::CeilToInt(CurrentHealth);
	int32 MaxHealth = FMath::CeilToInt(CurrentMaxHealth);

	FText HealthText = FText::Format(FText::FromString(TEXT("{0} / {1}")),Health,MaxHealth);

	HealthTextBlock->SetText(HealthText);
}

void UPlayerStatusWidget::BindPlayerStauts(ANovaPlayerController* PlayerController, ANovaPlayerState* PlayerState)
{
	if (!PlayerController || !PlayerState)
	{
		LOG(TEXT("Controller or PS is nullptr"));
		return;
	}

	AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UNovaAttributeSetBase::GetHealthAttribute())
			.AddUObject(this, &UPlayerStatusWidget::OnHealthChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UNovaAttributeSetBase::GetMaxHealthAttribute())
			.AddUObject(this, &UPlayerStatusWidget::OnHealthChanged);

		UpdateHelathBar();
	}

	//중복 바인딩 방지
	PlayerController->OnPlayerStateReady.RemoveDynamic(this, &UPlayerStatusWidget::BindPlayerStauts);
}