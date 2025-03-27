// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/HASPlayerAttributeSet.h"
#include <GameplayEffectExtension.h>

UHASPlayerAttributeSet::UHASPlayerAttributeSet()
{
	CurrentHealth.SetBaseValue(100.0f);
	CurrentHealth.SetCurrentValue(100.0f);

	MaxHealth.SetBaseValue(100.0f);
	MaxHealth.SetCurrentValue(100.0f);

	CurrentStamina.SetBaseValue(100.0f);
	CurrentStamina.SetCurrentValue(100.0f);

	MaxStamina.SetBaseValue(100.0f);
	MaxStamina.SetCurrentValue(100.0f);

	Speed.SetBaseValue(300.0f);
	Speed.SetCurrentValue(300.0f);
}

void UHASPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
}

void UHASPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		SetCurrentStamina(FMath::Clamp(GetCurrentStamina(), 0.0f, GetMaxStamina()));
	}
}

