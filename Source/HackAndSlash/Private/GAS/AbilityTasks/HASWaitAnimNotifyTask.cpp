// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/HASWaitAnimNotifyTask.h"
#include "Animations/HASAnimInstanceBase.h"

UHASWaitAnimNotifyTask* UHASWaitAnimNotifyTask::WaitAnimNotify(UGameplayAbility* OwningAbility, FString NotifyEvent)
{
	UHASWaitAnimNotifyTask* Task = NewAbilityTask<UHASWaitAnimNotifyTask>(OwningAbility);
	Task->Event = NotifyEvent;
	return Task;
}

void UHASWaitAnimNotifyTask::Activate()
{
	if (!Ability) return;

	if (UAbilitySystemComponent* AbilityComp = AbilitySystemComponent.Get())
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		if (UHASAnimInstanceBase* AnimInstance = Cast<UHASAnimInstanceBase>(ActorInfo->GetAnimInstance()))
		{
			AnimInstance->OnReceivedNotifyEvent.AddDynamic(this, &ThisClass::HandleOnReceivedNotifyEvent);			
		}
	}
}

void UHASWaitAnimNotifyTask::OnDestroy(bool AbilityEnding)
{
	if (UAbilitySystemComponent* AbilityComp = AbilitySystemComponent.Get())
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		if (UHASAnimInstanceBase* AnimInstance = Cast<UHASAnimInstanceBase>(ActorInfo->GetAnimInstance()))
		{
			AnimInstance->OnReceivedNotifyEvent.RemoveAll(this);
		}
	}
}

void UHASWaitAnimNotifyTask::HandleOnReceivedNotifyEvent(const FString& NotifyEvent)
{
	if (NotifyEvent == Event)
	{
		OnReceivedExactEvent.Broadcast();
	}
	else
	{
		OnReceivedOtherEvent.Broadcast();
	}
}
