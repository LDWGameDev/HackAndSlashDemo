// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HASSprintAbility.h"
#include <AbilitySystemComponent.h>
#include "GAS/AbilityTasks/HASWaitCancelledInputTask.h"
#include "HASGameplayTags.h"

UHASSprintAbility::UHASSprintAbility(const FObjectInitializer& ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerActor;
}

void UHASSprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (ActivateGE)
	{
		UGameplayEffect* GECDO = ActivateGE->GetDefaultObject<UGameplayEffect>();
		SprintGEHandle = ApplyGameplayEffectToOwner(CurrentSpecHandle, ActorInfo, ActivationInfo, GECDO, 1.0f, 1);
	}
	UHASWaitInputEventTask* WaitTask = UHASWaitInputEventTask::WaitInputEvent(this, FHASGameplayTags::Get().InputTag_Sprint, ETriggerEvent::Canceled);
	WaitTask->OnReceivedInputDelegate.AddDynamic(this, &ThisClass::HandleWaitInputTaskSuccess);
	WaitTask->Activate();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHASSprintAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UAbilitySystemComponent* AbilityComp = GetAbilitySystemComponentFromActorInfo())
	{
		AbilityComp->RemoveActiveGameplayEffect(SprintGEHandle, -1);
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHASSprintAbility::HandleWaitInputTaskSuccess(const FGameplayTag& InputTag, ETriggerEvent TriggerEvent)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
