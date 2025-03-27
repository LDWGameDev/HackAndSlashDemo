// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HASPlayerStatusSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnComboCounterUpdatedSignature, int32 ComboCount);

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASPlayerStatusSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public: 
	static UHASPlayerStatusSubsystem* Get(UObject* Object);

public:
	FOnComboCounterUpdatedSignature OnComboCountUpdated;

private:
	float ComboCounterResetTime = 2.0f;

	int32 ComboCounter;
	FTimerHandle ResetComboCounterTimerHandle;

public: 
	void IncrementComboCounter();
	
protected:
	UFUNCTION()
	void HandleResetComboCounterHandle();
};
