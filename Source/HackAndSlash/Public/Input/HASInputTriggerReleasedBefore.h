// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "HASInputTriggerReleasedBefore.generated.h"

/**
 * InputTrigger that triggers only once if the input is released before holding TimeOutThreshold seconds
 */
UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Released Before"))
class UHASInputTriggerReleasedBefore : public UInputTriggerTimedBase
{
	GENERATED_BODY()

protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

public:
	// How long the input has to be released before to cause trigger event, after holding pass this threshold, releasing the input won't cause trigger event 
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float TimeOutThreshold = 0.5f;
};
