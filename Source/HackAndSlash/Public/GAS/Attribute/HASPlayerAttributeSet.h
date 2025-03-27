// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Attribute/HASAttributeSetBase.h"
#include <AbilitySystemComponent.h>
#include "HASPlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASPlayerAttributeSet : public UHASAttributeSetBase
{
	GENERATED_BODY()

public: 
	UHASPlayerAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	
public: 
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UHASPlayerAttributeSet, Speed);

	UPROPERTY(BlueprintReadOnly, Category = "Player Attributes")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UHASPlayerAttributeSet, CurrentStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Player Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UHASPlayerAttributeSet, MaxStamina);
};
