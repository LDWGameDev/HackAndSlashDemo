// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include <InputTriggers.h>
#include <GameplayTagContainer.h>
#include "HASGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public: 
	UHASGameplayAbility();

public: 
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ForceApplyCost"))
	void K2_ApplyCost();
};
