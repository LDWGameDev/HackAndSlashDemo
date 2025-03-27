// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/HASInputTriggerReleasedBefore.h"

ETriggerState UHASInputTriggerReleasedBefore::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	const float TickHeldDuration = CalculateHeldDuration(PlayerInput, DeltaTime);

	ETriggerState State = Super::UpdateState_Implementation(PlayerInput, ModifiedValue, DeltaTime);

	if (TickHeldDuration < TimeOutThreshold && State == ETriggerState::None)
	{
		State = ETriggerState::Triggered;
	}

	return State;
}
