// Fill out your copyright notice in the Description page of Project Settings.


#include "NovaLogChannels.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Nova, "Nova");
DEFINE_LOG_CATEGORY(Nova)

void PrintViewport(float Time, const FColor& Color, const FString& Text)
{
	GEngine->AddOnScreenDebugMessage(-1, Time, Color, Text);
}