// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/HASWaitCancelledInputTask.h"
#include "GAS/HASAbilitySystemComponent.h"

UHASWaitInputEventTask* UHASWaitInputEventTask::WaitInputEvent(UGameplayAbility* OwningAbility, FGameplayTag InputTag, ETriggerEvent TriggerEvent)
{
	UHASWaitInputEventTask* Task = NewAbilityTask<UHASWaitInputEventTask>(OwningAbility);
	Task->InputTag = InputTag;
	Task->TriggerEvent = TriggerEvent;
	return Task;
}

void UHASWaitInputEventTask::Activate()
{
	UHASAbilitySystemComponent* AbilityComp = Cast<UHASAbilitySystemComponent>(AbilitySystemComponent.Get());
	if (AbilityComp)
	{
		ReceivedInputHandle = AbilityComp->OnReceivedInputEvent.AddUObject(this, &ThisClass::HandleOnReceivedInputEventOnAbilityComponent);
	}
	else
	{
		EndTask();
	}
	Super::Activate();
}

void UHASWaitInputEventTask::OnDestroy(bool AbilityEnding)
{
	UHASAbilitySystemComponent* AbilityComp = Cast<UHASAbilitySystemComponent>(AbilitySystemComponent.Get());
	if (AbilityComp)
	{
		AbilityComp->OnReceivedInputEvent.Remove(ReceivedInputHandle);
	}
	Super::OnDestroy(AbilityEnding);
}

void UHASWaitInputEventTask::HandleOnReceivedInputEventOnAbilityComponent(const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent)
{
	if (InputTag.MatchesTagExact(InInputTag) && TriggerEvent == InTriggerEvent)
	{
		OnReceivedInputDelegate.Broadcast(InputTag, TriggerEvent);
		EndTask();
	}
}
