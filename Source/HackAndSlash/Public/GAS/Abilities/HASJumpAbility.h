// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/HASGameplayAbility.h"
#include "HASJumpAbility.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASJumpAbility : public UHASGameplayAbility
{
	GENERATED_BODY()
	
public: 
	UHASJumpAbility(const FObjectInitializer& ObjectInitializer);

protected: 
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
