// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/HASInputConfig.h"


UInputAction* UHASInputConfig::FindNormalInputAction(const FGameplayTag& Tag)
{
	for (auto& IAIter : NormalInputActions)
	{
		if (IAIter.GameplayTag.MatchesTagExact(Tag))
		{
			return IAIter.InputAction;
		}
	}
	return nullptr;
}

UInputAction* UHASInputConfig::FindAbilityInputAction(const FGameplayTag& Tag)
{
	for (auto& IAIter : AbilityInputActions)
	{
		if (IAIter.GameplayTag.MatchesTagExact(Tag))
		{
			return IAIter.InputAction;
		}
	}
	return nullptr;
}
