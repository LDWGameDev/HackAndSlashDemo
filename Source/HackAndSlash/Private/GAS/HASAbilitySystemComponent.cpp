// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/HASAbilitySystemComponent.h"
#include "GAS/Abilities/HASGameplayAbility.h"

FActiveGameplayEffectHandle UHASAbilitySystemComponent::QuickApplyGE(TSubclassOf<UGameplayEffect> GE)
{
	if (!GE) return FActiveGameplayEffectHandle();
	FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GE, 1.0f, ContextHandle);
	return ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UHASAbilitySystemComponent::ApplyDefaultGEs()
{
	for (TSubclassOf<UGameplayEffect>& GEIter : DefaultGEs)
	{
		if (!GEIter) continue;
		FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GEIter, 1.0f, ContextHandle);
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UHASAbilitySystemComponent::GrantDefaultAbilities()
{
	for (TSubclassOf<UHASGameplayAbility>& AbilityIter : DefaultAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityIter));
	}
}

void UHASAbilitySystemComponent::ProcessTriggeredInputs(const TArray<FGameplayTag>& InputTags)
{
	FGameplayTagContainer InputTagContainer;
	for (const FGameplayTag& TagIter : InputTags)
	{
		InputTagContainer.AddTag(TagIter);
		OnReceivedInputEvent.Broadcast(TagIter, ETriggerEvent::Triggered);
	}

	for (FGameplayAbilitySpec& AbilitySpecIter : ActivatableAbilities.Items)
	{
		if (AbilitySpecIter.Ability && AbilitySpecIter.Ability->AbilityTags.HasAnyExact(InputTagContainer))
		{
			TryActivateAbility(AbilitySpecIter.Handle);
		}
	}
 }

void UHASAbilitySystemComponent::ProcessCancelledInputs(const TArray<FGameplayTag>& InputTags)
{
	for (const FGameplayTag& TagIter : InputTags)
	{
		OnReceivedInputEvent.Broadcast(TagIter, ETriggerEvent::Canceled);
	}
}

