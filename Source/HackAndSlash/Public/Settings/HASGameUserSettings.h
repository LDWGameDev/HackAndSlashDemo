// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "HASGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public: 
	static UHASGameUserSettings* Get();

private: 
	UPROPERTY(Config)
	float MouseSensitivity = 1.0f;

public: 
	float GetMouseSensitivity() { return MouseSensitivity; }
};
