// Fill out your copyright notice in the Description page of Project Settings.


#include "HASPlayerStatusSubsystem.h"
#include <Engine/GameInstance.h>

UHASPlayerStatusSubsystem* UHASPlayerStatusSubsystem::Get(UObject* Object)
{
	return UGameInstance::GetSubsystem<UHASPlayerStatusSubsystem>(Object->GetWorld()->GetGameInstance());
}

void UHASPlayerStatusSubsystem::IncrementComboCounter()
{
	++ComboCounter;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (TimerManager.IsTimerActive(ResetComboCounterTimerHandle))
	{
		TimerManager.ClearTimer(ResetComboCounterTimerHandle);
	}
	TimerManager.SetTimer(ResetComboCounterTimerHandle, this, &ThisClass::HandleResetComboCounterHandle, ComboCounterResetTime, false);
	OnComboCountUpdated.Broadcast(ComboCounter);
}

void UHASPlayerStatusSubsystem::HandleResetComboCounterHandle()
{
	ComboCounter = 0;
	OnComboCountUpdated.Broadcast(ComboCounter);
}