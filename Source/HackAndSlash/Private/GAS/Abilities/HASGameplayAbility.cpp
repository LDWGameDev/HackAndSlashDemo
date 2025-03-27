// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HASGameplayAbility.h"

UHASGameplayAbility::UHASGameplayAbility()
{

}

void UHASGameplayAbility::K2_ApplyCost()
{
	ApplyCost(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
}
