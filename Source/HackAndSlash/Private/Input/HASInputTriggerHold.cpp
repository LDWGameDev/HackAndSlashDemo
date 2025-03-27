// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/HASInputTriggerHold.h"

ETriggerState UHASInputTriggerHold::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	ETriggerState State = Super::UpdateState_Implementation(PlayerInput, ModifiedValue, DeltaTime);

	if (HeldDuration >= HoldTimeThreshold && State == ETriggerState::Ongoing && !bTriggered)
	{
		State = ETriggerState::Triggered;
		bTriggered = true;
	}

	if (State == ETriggerState::None)
	{
		bTriggered = false;
	}

	return State;
}
