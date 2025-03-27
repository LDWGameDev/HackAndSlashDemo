// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "HASInputTriggerHold.generated.h"

/**
 * InputTrigger that causes Trigger state one time after holding input for HoldTimeThreshold seconds
 */
UCLASS(NotBlueprintType, MinimalAPI, meta = (DisplayName = "Hold Trigger Once"))
class UHASInputTriggerHold : public UInputTriggerTimedBase
{
	GENERATED_BODY()

protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

public:
	virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override { return ETriggerEventsSupported::Ongoing; }
	
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float HoldTimeThreshold = 0.5f;

	bool bTriggered = false;
};
