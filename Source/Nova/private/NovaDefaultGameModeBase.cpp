// Fill out your copyright notice in the Description page of Project Settings.


#include "NovaDefaultGameModeBase.h"
#include "Subsystem/NovaCharacterDataSubsystem.h"
#include "Data/NovaCharacterData.h"
#include "Character/Player/PlayerBase.h"
#include "Character/Player/NovaPlayerController.h"

#include "NovaLogChannels.h"

ANovaDefaultGameModeBase::ANovaDefaultGameModeBase()
{

}

void ANovaDefaultGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (UNovaCharacterDataSubsystem* CharacterData = GameInstance->GetSubsystem<UNovaCharacterDataSubsystem>())
		{
			CharacterData->LoadPlayerData();
			OnPlayerClassLoaded(NewPlayer);
		}
	}
	
}

void ANovaDefaultGameModeBase::OnPlayerClassLoaded(APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		LOG(TEXT("No PlayerController."));
		return;
	}

	UNovaCharacterDataSubsystem* CharacterDataSubsystem = GetGameInstance()->GetSubsystem<UNovaCharacterDataSubsystem>();

	if (!CharacterDataSubsystem)
	{
		LOG(TEXT("No UNovaCharacterDataSubsystem."));
		return;
	}

	//캐릭터 선택 구현 전까지 첫번째 데이터를 사용한다.
	if (!CharacterDataSubsystem->LoadedPlayerDataArray.IsValidIndex(0))
	{
		LOG(TEXT("No loaded PlayerData."));
		return;
	}

	UNovaCharacterData* PlayerData = CharacterDataSubsystem->LoadedPlayerDataArray[0];

	if (!PlayerData || PlayerData->CharacterPawn.IsNull())
	{
		LOG(TEXT("No PlayerData."));
		return;
	}
	//

	if (UClass* LoadedClass = PlayerData->CharacterPawn.LoadSynchronous())
	{
		AActor* StartActor = FindPlayerStart(PlayerController);
		FTransform	StartTransform = StartActor ? StartActor->GetActorTransform() : FTransform::Identity;

		if (APlayerBase* PlayerPawn = GetWorld()->SpawnActor<APlayerBase>(LoadedClass, StartTransform))
		{
			PlayerController->Possess(PlayerPawn);
			PlayerPawn->InitCharacterData(PlayerData);
		}
	}
	else
	{
		LOG(TEXT("Player Spawn Failed"));
	}
}
