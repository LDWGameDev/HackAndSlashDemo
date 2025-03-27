// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/HASEnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>

void UHASEnhancedInputComponent::InitInputs(UHASInputConfig* Config, ULocalPlayer* LocalPlayer)
{
	if (!Config || !LocalPlayer || Config->InputMappingContexts.Num() == 0) return;

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLPSS = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		ClearActionBindings();
		EnhancedInputLPSS->ClearAllMappings();

		FHASInputMappingContext& DefaultInputMappingContext = Config->InputMappingContexts[0];

		FModifyContextOptions Options{};
		Options.bIgnoreAllPressedKeysUntilRelease = false;
		EnhancedInputLPSS->AddMappingContext(DefaultInputMappingContext.InputMappingContext, DefaultInputMappingContext.Priority, Options);

		// TODO: register remaining MappingContexts from Config for later swapping
	}

	BindAllAbilityInputActions(this, Config, ETriggerEvent::Triggered, &ThisClass::HandleAbilityInputTriggered);
	BindAllAbilityInputActions(this, Config, ETriggerEvent::Canceled, &ThisClass::HandleAbilityInputCancelled);
}

void UHASEnhancedInputComponent::ProcessCachedInputs()
{
	if (CachedTriggeredInputs.Num() > 0)
	{
		OnProcessedTriggeredInputsDelegate.Broadcast(CachedTriggeredInputs);
	}

	if (CachedCancelledInputs.Num() > 0)
	{
		OnProcessedCancelledInputsDelegate.Broadcast(CachedCancelledInputs);
	}

	CachedTriggeredInputs.Empty();
	CachedCancelledInputs.Empty();
}

void UHASEnhancedInputComponent::HandleAbilityInputTriggered(const FInputActionValue& Value, FGameplayTag Tag)
{
	CachedTriggeredInputs.AddUnique(Tag);
}

void UHASEnhancedInputComponent::HandleAbilityInputCancelled(const FInputActionValue& Value, FGameplayTag Tag)
{
	CachedCancelledInputs.AddUnique(Tag);
}
