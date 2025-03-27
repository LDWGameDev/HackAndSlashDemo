// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include <InputTriggers.h>
#include "HASAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReceivedInputEventSignature, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent);

class UGameplayEffect;
class UHASGameplayAbility;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public: 
	FOnReceivedInputEventSignature OnReceivedInputEvent;
	
protected: 
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<UGameplayEffect>> DefaultGEs;
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<UHASGameplayAbility>> DefaultAbilities;

public:
	FActiveGameplayEffectHandle QuickApplyGE(TSubclassOf<UGameplayEffect> GE);

	void ApplyDefaultGEs();
	void GrantDefaultAbilities();

	void ProcessTriggeredInputs(const TArray<FGameplayTag>& InputTags);
	void ProcessCancelledInputs(const TArray<FGameplayTag>& InputTags);
};
