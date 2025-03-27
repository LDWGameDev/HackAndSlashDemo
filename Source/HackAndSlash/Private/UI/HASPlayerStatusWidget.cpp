// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASPlayerStatusWidget.h"
#include "UI/HASGhostProgressBarWidget.h"
#include <AbilitySystemComponent.h>
#include "GAS/Attribute/HASPlayerAttributeSet.h"
#include "Characters/Player/HASPlayerCharacter.h"

void UHASPlayerStatusWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (HealthBar)
	{
		HealthBar->SetProgressBarValue(1.0f);
	}
	if (StaminaBar)
	{
		StaminaBar->SetProgressBarValue(1.0f);
	}
}

void UHASPlayerStatusWidget::BindToAttributeChanges()
{
	if (AHASPlayerCharacter* OwningChar = Cast<AHASPlayerCharacter>(GetOwningPlayerPawn()))
	{
		if (!OwningChar->GetAbilitySystemComponent() || !OwningChar->PlayerAttributeSet) return;
		FOnGameplayAttributeValueChange& CurrentHealthDelegate = OwningChar->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(OwningChar->PlayerAttributeSet->GetCurrentHealthAttribute());
		CurrentHealthDelegate.AddUObject(this, &ThisClass::HandleOnChangedCurrentHealthAttribute);

		FOnGameplayAttributeValueChange& MaxHealthDelegate = OwningChar->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(OwningChar->PlayerAttributeSet->GetMaxHealthAttribute());
		MaxHealthDelegate.AddUObject(this, &ThisClass::HandleOnChangedMaxHealthAttribute);

		FOnGameplayAttributeValueChange& CurrentStaminaDelegate = OwningChar->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(OwningChar->PlayerAttributeSet->GetCurrentStaminaAttribute());
		CurrentStaminaDelegate.AddUObject(this, &ThisClass::HandleOnChangedCurrentStaminaAttribute);

		FOnGameplayAttributeValueChange& MaxStaminaDelegate = OwningChar->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(OwningChar->PlayerAttributeSet->GetMaxStaminaAttribute());
		MaxStaminaDelegate.AddUObject(this, &ThisClass::HandleOnChangedMaxStaminaAttribute);

		UHASPlayerAttributeSet* PlayerAttributeSet = GetPlayerAttributeSet();
		if (HealthBar)
		{
			HealthBar->SetProgressBarValue(PlayerAttributeSet->GetCurrentHealth() / PlayerAttributeSet->GetMaxHealth(), true);
		}
		if (StaminaBar)
		{
			StaminaBar->SetProgressBarValue(PlayerAttributeSet->GetCurrentStamina() / PlayerAttributeSet->GetMaxStamina(), true);
		}
	}
}

UHASPlayerAttributeSet* UHASPlayerStatusWidget::GetPlayerAttributeSet()
{
	if (AHASPlayerCharacter* OwningChar = Cast<AHASPlayerCharacter>(GetOwningPlayerPawn()))
	{
		return OwningChar->PlayerAttributeSet;
	}
	return nullptr;
}

void UHASPlayerStatusWidget::HandleOnChangedCurrentHealthAttribute(const FOnAttributeChangeData& ChangeData)
{
	UHASPlayerAttributeSet* PlayerAttributeSet = GetPlayerAttributeSet();
	if (HealthBar && PlayerAttributeSet)
	{
		HealthBar->SetProgressBarValue(ChangeData.NewValue / PlayerAttributeSet->GetMaxHealth());
	}
}

void UHASPlayerStatusWidget::HandleOnChangedMaxHealthAttribute(const FOnAttributeChangeData& ChangeData)
{
	UHASPlayerAttributeSet* PlayerAttributeSet = GetPlayerAttributeSet();
	if (HealthBar && PlayerAttributeSet)
	{
		HealthBar->SetProgressBarValue(PlayerAttributeSet->GetCurrentHealth() / ChangeData.NewValue);
	}
}

void UHASPlayerStatusWidget::HandleOnChangedCurrentStaminaAttribute(const FOnAttributeChangeData& ChangeData)
{
	UHASPlayerAttributeSet* PlayerAttributeSet = GetPlayerAttributeSet();
	if (StaminaBar && PlayerAttributeSet)
	{
		StaminaBar->SetProgressBarValue(ChangeData.NewValue / PlayerAttributeSet->GetMaxStamina());
	}
}

void UHASPlayerStatusWidget::HandleOnChangedMaxStaminaAttribute(const FOnAttributeChangeData& ChangeData)
{
	UHASPlayerAttributeSet* PlayerAttributeSet = GetPlayerAttributeSet();
	if (StaminaBar && PlayerAttributeSet)
	{
		StaminaBar->SetProgressBarValue(PlayerAttributeSet->GetCurrentStamina() / ChangeData.NewValue);
	}
}
