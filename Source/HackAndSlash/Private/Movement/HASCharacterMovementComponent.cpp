// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/HASCharacterMovementComponent.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystemComponent.h>
#include "GAS/Attribute/HASPlayerAttributeSet.h"
#include "Characters/Player/HASPlayerCharacter.h"
#include "HASGameplayTags.h"
#include <GameplayEffectTypes.h>

void UHASCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}

float UHASCharacterMovementComponent::GetMaxSpeed() const
{
	AHASPlayerCharacter* Owner = GetOwner<AHASPlayerCharacter>();
	if (!Owner || !Owner->GetAbilitySystemComponent() || !Owner->PlayerAttributeSet) return Super::GetMaxSpeed();

	bool bSprinting = (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(FHASGameplayTags::Get().Action_Sprint)) ? true : false;
	// float Multiplier = bSprinting ? 1.5f : 1.0f;   // DONE: change Speed attribute instead of a fixed multiplier value of 1.5

	switch (MovementMode)
	{
		case EMovementMode::MOVE_Walking:
		case EMovementMode::MOVE_NavWalking:
		{
			return Owner->PlayerAttributeSet->GetSpeed()/* * Multiplier*/;
		}
		default:
		{
			return Super::GetMaxSpeed();
		}
	}
}

void UHASCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	AHASPlayerCharacter* Owner = GetOwner<AHASPlayerCharacter>();
	if (!FallingActionGE || !Owner || !Owner->GetAbilitySystemComponent()) return;

	UAbilitySystemComponent* AbilityComp = Owner->GetAbilitySystemComponent();
	switch (MovementMode)
	{
		case EMovementMode::MOVE_Falling:
		{
			FGameplayEffectContextHandle ContextHandle = AbilityComp->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = AbilityComp->MakeOutgoingSpec(FallingActionGE, 1.0f, ContextHandle);
			EffectHandle = AbilityComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			break;
		}
	}

	if (PreviousMovementMode == EMovementMode::MOVE_Falling)
	{
		AbilityComp->RemoveActiveGameplayEffect(EffectHandle, -1);
	}
}

