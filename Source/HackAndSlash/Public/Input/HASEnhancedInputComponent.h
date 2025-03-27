// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include <GameplayTagContainer.h>
#include "HASInputConfig.h"
#include "HASEnhancedInputComponent.generated.h"

class UInputAction;
class UHASInputConfig;
class ULocalPlayer;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessedCachedInputsSignature, TArray<FGameplayTag> Inputs);

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	FOnProcessedCachedInputsSignature OnProcessedTriggeredInputsDelegate;
	FOnProcessedCachedInputsSignature OnProcessedCancelledInputsDelegate;

private:
	TArray<FGameplayTag> CachedTriggeredInputs;
	TArray<FGameplayTag> CachedCancelledInputs;
	
public: 
	void InitInputs(UHASInputConfig* Config, ULocalPlayer* LocalPlayer);

	template<class UserClass, typename FuncType>
	void BindNormalInputActionByTag(UserClass* Object, UHASInputConfig* InputConfig, const FGameplayTag& Tag, ETriggerEvent TriggerEvent, FuncType Func);

	template<class UserClass, typename FuncType>
	void BindAbilityInputActionByTag(UserClass* Object, UHASInputConfig* InputConfig, const FGameplayTag& Tag, ETriggerEvent TriggerEvent, FuncType Func);

	template<class UserClass, typename FuncType>
	void BindAllAbilityInputActions(UserClass* Object, UHASInputConfig* InputConfig, ETriggerEvent TriggerEvent, FuncType Func);

	void ProcessCachedInputs();

private: 
	void HandleAbilityInputTriggered(const FInputActionValue& Value, FGameplayTag Tag);
	void HandleAbilityInputCancelled(const FInputActionValue& Value, FGameplayTag Tag);
};

template<class UserClass, typename FuncType>
void UHASEnhancedInputComponent::BindNormalInputActionByTag(UserClass* Object, UHASInputConfig* InputConfig, const FGameplayTag& Tag, ETriggerEvent TriggerEvent, FuncType Func)
{
	if (!InputConfig || !Object) return;
	UInputAction* InputAction = InputConfig->FindNormalInputAction(Tag);
	
	if (!InputAction) return;
	BindAction(InputAction, TriggerEvent, Object, Func);
}

template<class UserClass, typename FuncType>
void UHASEnhancedInputComponent::BindAbilityInputActionByTag(UserClass* Object, UHASInputConfig* InputConfig, const FGameplayTag& Tag, ETriggerEvent TriggerEvent, FuncType Func)
{
	if (!InputConfig || !Object) return;
	UInputAction* InputAction = InputConfig->FindAbilityInputAction(Tag);

	if (!InputAction) return;
	BindAction(InputAction, TriggerEvent, Object, Func);
}

template<class UserClass, typename FuncType>
void UHASEnhancedInputComponent::BindAllAbilityInputActions(UserClass* Object, UHASInputConfig* InputConfig, ETriggerEvent TriggerEvent, FuncType Func)
{
	if (!InputConfig || !Object) return;
	for (FHASInputAction& AbilityInputIter : InputConfig->AbilityInputActions)
	{
		BindAction(AbilityInputIter.InputAction, TriggerEvent, Object, Func, AbilityInputIter.GameplayTag);
	}
}