// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Nova, Log, All);

#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))
#define	LOG(Format, ...)	UE_LOG(Nova, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define	LOGSTRING(Str)		UE_LOG(Nova, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *Str)
#define LOG_NET(Format, ...) { \
        const FString NetPrefix = GetWorld()->IsNetMode(NM_Client) ? TEXT("[Client] ") : TEXT("[Server] "); \
        UE_LOG(Nova, Warning, TEXT("%s%s : %s"), *NetPrefix, *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)); \
    }

void PrintViewport(float Time, const FColor& Color, const FString& Text);
