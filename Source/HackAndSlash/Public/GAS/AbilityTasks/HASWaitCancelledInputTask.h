// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include <InputTriggers.h>
#include "HASWaitCancelledInputTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReceivedInputSignature, const FGameplayTag&, InputTag, ETriggerEvent, TriggerEvent);

class UHASAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASWaitInputEventTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UHASWaitInputEventTask* WaitInputEvent(UGameplayAbility* OwningAbility, FGameplayTag InputTag, ETriggerEvent TriggerEvent);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnding) override;

public: 
	UPROPERTY(BlueprintAssignable)
	FOnReceivedInputSignature OnReceivedInputDelegate;

private: 
	FGameplayTag InputTag;
	ETriggerEvent TriggerEvent;
	FDelegateHandle ReceivedInputHandle;

private: 
	UFUNCTION()
	void HandleOnReceivedInputEventOnAbilityComponent(const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent);
};
