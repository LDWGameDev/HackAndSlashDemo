// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HASJumpAbility.h"
#include "Characters/Player/HASPlayerCharacter.h"

UHASJumpAbility::UHASJumpAbility(const FObjectInitializer& ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UHASJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//if (ActorInfo)
	//{
	//	if (AHASPlayerCharacter* PlayerChar = Cast<AHASPlayerCharacter>(ActorInfo->AvatarActor))
	//	{
	//		PlayerChar->Jump();
	//	}
	//}
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHASJumpAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
