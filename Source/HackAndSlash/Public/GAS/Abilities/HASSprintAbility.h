// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/HASGameplayAbility.h"
#include <GameplayTagContainer.h>
#include <EnhancedInputComponent.h>
#include "HASSprintAbility.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASSprintAbility : public UHASGameplayAbility
{
	GENERATED_BODY()

public: 
	UHASSprintAbility(const FObjectInitializer& ObjectInitializer);
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public: 
	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	TSubclassOf<UGameplayEffect> ActivateGE;

private: 
	FActiveGameplayEffectHandle SprintGEHandle;

private: 
	UFUNCTION()
	void HandleWaitInputTaskSuccess(const FGameplayTag& InputTag, ETriggerEvent TriggerEvent);
};

