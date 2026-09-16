// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerBase.h"
#include "Character/Player/NovaPlayerState.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Component/NovaEnhancedInputComponent.h"
#include "Ability/NovaAbilitysystemComponent.h"

#include "Subsystem/NovaCharacterDataSubsystem.h"
#include "Character/Player/PlayerAnimInstance.h"
#include "Data/NovaPlayerData.h"
#include "Data/InputActionDataAsset.h"

#include "NovaGameplayTags.h"
#include "NovaLogChannels.h"

APlayerBase::APlayerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PlayerMainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	PlayerSpringArm->SetupAttachment(GetMesh());
	PlayerMainCamera->SetupAttachment(PlayerSpringArm);

	bUseControllerRotationYaw = false; // 즉시 스냅 방지
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;	// 캐릭터가 이동하는 방향으로 회전한다.
	GetCharacterMovement()->bUseControllerDesiredRotation = true;	//원하는 방향으로 회전
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.f, 0.0f);	//캐릭터 회전 보간
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ANovaPlayerState* PS = GetPlayerState<ANovaPlayerState>())
	{
		AbilitySystemComponent = PS->GetAbilitySystemComponent();

		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->InitAbilityActorInfo(PS, this);

			NovaAbilitySystemComponent = GetNovaAbilitySystemComponent();
		}

		AttributeSet = PS->GetAttributeSet();
	}

}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//불러올 때 태그나 다른 걸로 확인해서 불러오게 변경
	UNovaCharacterDataSubsystem* CharacterDataSubsystem = GetGameInstance()->GetSubsystem<UNovaCharacterDataSubsystem>();
	if (!IsValid(CharacterDataSubsystem))
	{
		LOG(TEXT("CharacterData is nullptr"));
		return;
	}

	if (UNovaPlayerData* PlayerInputData = Cast<UNovaPlayerData>(CharacterDataSubsystem->LoadedPlayerDataArray[0]))
	{
		UInputActionDataAsset* InputData = PlayerInputData->InputData;

		if (UNovaEnhancedInputComponent* EIComp = Cast<UNovaEnhancedInputComponent>(PlayerInputComponent))
		{
			EIComp->BindNativeInputAction(InputData, NovaGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &APlayerBase::Input_Move);

			EIComp->BindAbilityInputAction(InputData, this, &APlayerBase::Input_AbilityTriggered, &APlayerBase::Input_AbilityCompleted);
		}
	}	
}

void APlayerBase::InitCharacterData(UNovaCharacterData* CharacterData)
{
	Super::InitCharacterData(CharacterData);

	CharacterAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

void APlayerBase::Input_Move(const FInputActionValue& IAValue)
{
	const FVector2D Value = IAValue.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, Value.Y);
	AddMovementInput(RightDirection, Value.X);
}

void APlayerBase::Input_AbilityTriggered(FGameplayTag InputTag)
{
	NovaAbilitySystemComponent->AbilityInputTriggered(InputTag);
}

void APlayerBase::Input_AbilityCompleted(FGameplayTag InputTag)
{
	NovaAbilitySystemComponent->AbilityInputCompleted(InputTag);
}

UNovaAbilitySystemComponent* APlayerBase::GetNovaAbilitySystemComponent()
{
	if (!NovaAbilitySystemComponent)
	{
		NovaAbilitySystemComponent = Cast<UNovaAbilitySystemComponent>(AbilitySystemComponent);
	}

	return NovaAbilitySystemComponent;
}
