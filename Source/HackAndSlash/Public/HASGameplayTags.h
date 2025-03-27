// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayTagContainer.h>

/**
 * 
 */
class HACKANDSLASH_API FHASGameplayTags
{
public:
	FGameplayTag InputTag_CursorDelta;
	FGameplayTag InputTag_Movement;
	FGameplayTag InputTag_LightAttack;
	FGameplayTag InputTag_HeavyAttack;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Dodge;
	FGameplayTag InputTag_Sprint;

	FGameplayTag Action_Sprint;
	FGameplayTag Action_Jump;
	FGameplayTag Action_Fall;
	FGameplayTag Action_GroundAttack;
	FGameplayTag Action_AirAttack;
	FGameplayTag Action_Take;
	FGameplayTag Action_ReceiveLightAttack;
	FGameplayTag Action_ReceiveHeavyAttack;
	FGameplayTag Action_ReceiveKnockup;
	FGameplayTag Action_ReceiveKnockback;
	FGameplayTag Action_ReceiveKnockdown;

	FGameplayTag State_CanDoNextCombo;
	FGameplayTag State_Dead;

	FGameplayTag Stat_StaminaConsumption;

	FGameplayTag GC_Poison;

public:
	static FHASGameplayTags& Get()
	{
		static FHASGameplayTags Instance;
		return Instance;
	}
	void InitAllTags();

private: 
	void AddTag(FGameplayTag& Tag, const FName& TagContent, const FString& TagDescription = TEXT(""));
};

