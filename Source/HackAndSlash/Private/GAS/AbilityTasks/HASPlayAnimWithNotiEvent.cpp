// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/HASPlayAnimWithNotiEvent.h"
#include "GAS/HASAbilitySystemComponent.h"

UHASPlayAnimWithNotiEvent* UHASPlayAnimWithNotiEvent::PlayAnimationWithNotifyEvent(UGameplayAbility* OwningAbility)
{
	UHASPlayAnimWithNotiEvent* Task = NewAbilityTask<UHASPlayAnimWithNotiEvent>(OwningAbility);
	return Task;
}

void UHASPlayAnimWithNotiEvent::Activate()
{
	UHASAbilitySystemComponent* AbilityComp = Cast<UHASAbilitySystemComponent>(AbilitySystemComponent.Get());
	if (AbilityComp)
	{
		if (AbilityComp->AbilityActorInfo->GetAnimInstance())
		{
			UE_LOG(LogTemp, Log, TEXT("VALID anim instance"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("INVALID anim instance"));
		}
	}
	else
	{
		EndTask();
	}
	Super::Activate();
}

void UHASPlayAnimWithNotiEvent::OnDestroy(bool bInOwnerFinished)
{
	

	Super::OnDestroy(bInOwnerFinished);
}
